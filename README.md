# CS 100 Programming Project
> Winter 2020 - Alejandro Sherman (862062898) and Ernie Hung (862153636)

## Introduction
Our project is the implementation of a basic command shell, complete with a user interface, and functionality of certain commands and connectors. The shell allows for the use of standard commands after they are input by a user, such as `exit` and `test` (both self designed), as well as the use of three connectors that allow users to execute multiple commands at once, and four more connectors that allow for input and output redirection. These connectors are "||" (or), "&&" (and), ";" (semi), "|" (pipe), "<" (input), ">" (output_t), and ">>" (output_a). All commands, save for the self designed ones as mentioned above, are executed in a fork are passed to the linux system via `execvp()`. The system runs commands and operators from left to right, unless parenthesis are entered, in which case, commands and operators will be executed in the proper precedence. The composite design pattern was utilized to implement the commands and the connectors, both inheriting from the base class, and each being superclasses of their own. The project is made in C++ and features have been implemented using C++ classes and functions.
## Diagram
![OMT_Diagram](https://github.com/cs100/assignment-empty_string/blob/master/images/OMT_Diagram.png?raw=true)

## Classes
### main.cpp
The area that the user interacts with when they use the shell

* `#includes` all the other classes from the header folder
* displays the command prompt `guest@rshell:~$`
* user's input is echoed as they type it
* utilizes Shunting Yard algorithm to handle parenthesis and precedence
* executes commands similar to how a calculator does
* using the postfix expression from the SY algorithm, an expression tree is created and the root node is executed

### base.h
A class that other frameworks build off of, an abstract base class

* `Base()` : simple constructor
* comprised of a virtual function and a pure virtual function
* class is designed to be a superclass only
* `parsing(string)` : takes user input as a string, parses it, and returns a vector of string tokens
* subsequent classes inherit parsing
* any input following pound: `#` are ignored in parsing
* `execute() = 0;` : a pure virtual function as every subclass must implement it's own execute function
* `getPath() = 0;` : a pure virtual function as every subclass have a `getPath()` to prevent the program from crashing when using the function

### Testing
Less of a class, and more of a representation of the testing frameworks used

* `unit_tests` : individually designed tests made to test specific program functions and are run together using the google test submodule
* `integration_tests` : I/O tests that mimic the overall combined functionality of the completed program and has a suite of tests each focusing on a certain combination of features

### command.h
A class that creates and executes commands, and allows for the special command `exit` to inherit from

* Commands are created in the main using the format `new Command(string, vector<string>)`
* `Command() : Base()` + `Command(string, vector<string> ) : Base()`: command constructors
* On construction the command is passed in as a string, and the arguments are passed in as a vector of strings
* `execute()` : creates a fork and attempts to execute the command, if succeeds returns true, and returns false otherwise
* `getPath()` : the command class is the only one that is intended to use the this function, simply returns the "command" of a command object to allow for input and output redirection
* `parsing(string)` : inherited from the base class

### connector.h
A class that connectors specialize from

* utilizes two objects of the base class to account for a left and right of the operator
* `Connector() : Base()` + `Connector (Base*, Base*) : Base()` : connector constructors
* `execute() = 0;` : redeclared as a pure virtual function so that every operator that inherits from this class must define it's own execute
* `getPath() = 0;` : redeclared as a pure virtual function so that every operator that inherits from this class must define it's own `getPath()` so that the program can handle every situation without crashing


### exit.h
A self designed rshell command to exit the rshell

* an exit object is created in the main when a command is created that has "exit" as the passed in command
* `execute()` : a self designed function that exits the rshell, done by calling exit(0);
* `getPath()` : obligatory `getPath()` implementation, simply returns "exit"
* inherits command defined features
* the rshell will keep running until this command is entered

### test.h
A self designed rshell command to test the existence and types of objects located on the local or absolute path

* a test object is created in the main when a command is created that has "test" as the passed in command or when an input is surrounded by `[ ]`
* these two types are known as "literal" and "symbolic" respectively
* `execute()` : a self designed function that tests the status an object on the specified path according to the flags -e -f or -d with -e being assumed if no flag specified
* `getPath()` : obligatory `getPath()` implementation, simply returns "[" or "test"
* performs the execution using `stat()` function and `S_ISDIR()`, `S_ISREG()` macros
* returns true if passes and outputs `(TRUE)` and is false and outputs `(FALSE)` if fails


### and.cpp
A class that implements the rshell "&&" connector

* `And() : Connector` + `And(Base*, Base*) : Connector()` : And constructors
* utilizes the left and right base pointers from the connector class
* `execute()` : executes the commands according to the and operator, as such both commands on the left and right only execute when both commands are valid
* `getPath()` : obligatory `getPath()` implementation, if called on a connector such as this, returns `left->getPath()` + " && " + `right->getPath()`, this will result in a failure that the system can adequately handle
* commands are executed by utilizing the command class execute

### or.cpp
A class that implements the rshell "||" connector

* `Or() : Connector` + `Or(Base*, Base*) : Connector()` : Or constructors
* utilizes the left and right base pointers from the connector class
* `execute()` : executes the commands according to the or operator, only one command executes if it is valid
* `getPath()` : obligatory `getPath()` implementation, if called on a connector such as this, returns `left->getPath()` + " || " + `right->getPath()`, this will result in a failure that the system can adequately handle
* commands are executed by utilizing the command class execute

### semi.cpp
A class that implements the rshell ";" connector

* `Semi() : Connector` + `Semi(Base*, Base*) : Connector()` : Semi constructors
* utilizes the left and right base pointers from the connector class
* `execute()` : executes the commands according to the semicolon operator, both commands attempt to execute
* `getPath()` : obligatory `getPath()` implementation, if called on a connector such as this, returns `left->getPath()` + " ; " + `right->getPath()`, this will result in a failure that the system can adequately handle
* commands are executed by utilizing the command class execute

### pipes.cpp
A class that implements the rshell "|" connector

* `Pipes() : Connector` + `Pipes(Base*, Base*) : Connector()` : Pipes constructors
* utilizes the left and right base pointers from the connector class
* `execute()` : using the functions of `dup()`, `dup2()`, and `pipe()`, this function reads output from a program on the left side of the pipe, and writes the previous output as an input to a program on the right side of the pipe
* `getPath()` : obligatory `getPath()` implementation, if called on a connector such as this, returns `left->getPath()` + " | " + `right->getPath()`, this will result in a failure that the system can adequately handle
* commands are executed by utilizing the command class execute

### input.cpp
A class that implements the rshell "<" connector

* `Input() : Connector` + `Input(Base*, Base*) : Connector()` : Input constructors
* utilizes the left and right base pointers from the connector class
* `execute()` : using the functions of `dup()`, `dup2()`, `open()` and `close()`, this function reads output from a file on the right side of the operator, and feeds the previous output as an input to the program on the left side of the operator
* uses `right->getPath()` to get access to the name of the file that will be read from
* `getPath()` : obligatory `getPath()` implementation, if called on a connector such as this, returns `left->getPath()` + " < " + `right->getPath()`, this will result in a failure that the system can adequately handle
* commands are executed by utilizing the command class execute

### output_t.cpp
A class that implements the rshell ">" connector

* `Output_T() : Connector` + `Output_T(Base*, Base*) : Connector()` : Output_T constructors
* utilizes the left and right base pointers from the connector class
* `execute()` : using the functions of `dup()`, `dup2()`, `open()` and `close()`, this function reads output from a program on the left side of the operator, and provides the previous output as an input to a file on the right side of the operator
* uses `right->getPath()` to get access to the name of the file that will be written to
* if the file being written to didn't already exist, the file is created by using the flag `O_CREAT` on the `open()` function
* this version of the output connector in specific will overwrite the specified file if it already exists, this is done by using the flag `O_TRUNC` on the `open()` function
* `getPath()` : obligatory `getPath()` implementation, if called on a connector such as this, returns `left->getPath()` + " > " + `right->getPath()`, this will result in a failure that the system can adequately handle
* commands are executed by utilizing the command class execute

### output_a.cpp
A class that implements the rshell ">>" connector

* `Output_A() : Connector` + `Output_A(Base*, Base*) : Connector()` : Output_A constructors
* utilizes the left and right base pointers from the connector class
* `execute()` : using the functions of `dup()`, `dup2()`, `open()` and `close()`, this function reads output from a program on the left side of the operator, and provides the previous output as an input to a file on the right side of the operator
* uses `right->getPath()` to get access to the name of the file that will be written to
* if the file being written to didn't already exist, the file is created by using the flag `O_CREAT` on the `open()` function
* this version of the output connector in specific will write to the end of the specified file if it already exists and this is done by using the flag `O_APPEND` on the `open()` function
* `getPath()` : obligatory `getPath()` implementation, if called on a connector such as this, returns `left->getPath()` + " >> " + `right->getPath()`, this will result in a failure that the system can adequately handle
* commands are executed by utilizing the command class execute

## Prototypes/Research
* `fork()` is used to create a new process, called child process
* under the child process, `execvp()` allows the child process to run a different program
* `waitpid()` allows the parent process to wait for the child process to finish and terminate before proceeding, this prevents memory leaks and zombie process from happening
* `WIFEXITED(status)` and `WEXITSTATUS(status)` are helpful functions that can more easily recognize the return status of commands in the program
* During the use of rshell, when a new command is executed, the parent process will fork and create a new child process, which will then attempt to perform the command
* According to the tokens received, commands will be created and executed depending on if they are valid or invalid, and depend on what operators are present
* While the process is being executed by the child, the parent process will wait for the child to finish in order to continue

## Development and Testing Roadmap
[#1](../../issues/1) Implement and test: Base Class

[#2](../../issues/2) Implement and test: Connector

[#3](../../issues/3) Implement and test: Command

[#4](../../issues/4) Implement and test: Exit

[#5](../../issues/5) Implement and test: Comment(in parsing)

[#6](../../issues/6) Implement and test: And

[#7](../../issues/7) Implement and test: Or

[#8](../../issues/8) Implement and test: Semi

[#9](../../issues/9) Implement and test: Main(user interface)

[#10](../../issues/33) Implement and test: Test

[#11](../../issues/34) Implement and test: Precedence(SY in main)

[#12](../../issues/40) Implement and test: getPath

[#13](../../issues/39) Implement and test: Input Redirection

[#14](../../issues/41) Implement and test: Output Redirection

[#15](../../issues/46) Implement and test: Pipes
