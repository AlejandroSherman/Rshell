# CS 100 Programming Project
> Winter 2020 - Alejandro Sherman (862062898) and Eddie...

## Introduction
Our project is the implementation of a basic command shell, complete with a user interface, and functionality of certain commands and connectors. The shell will allow for the use of standard commands after they are input by a user, such as `exit`, as well as the use of three connectors that allow users to execute multiple commands at once. These connectors are "||" (or), "&&" (and), and ";" (semi). The composite design pattern will be utilized to implement the commands and the connectors. The project will be created in C++ and features will be implemented using C++ classes and functions.

## Diagram
![OMT_Diagram](https://github.com/cs100/assignment-empty_string/blob/master/images/OMT_Diagram.png?raw=true)

## Classes
### user.cpp
The area that the user interacts with when they use the shell

* displays the command prompt `guest@rshell:~$`
* takes the user input and sends it where it needs to go
* `echo()` : prints the input back to the user
* `execute()` : a self designed function that performs the desired task

### base.h
A class that other frameworks build off of

* comprised of virtual functions as the class is meant to be used as a superclass
* `parse()` : parses user input using tokens
* parse can be rewritten by other classes, but is optional
* `execute()` : a pure virtual function as every subclass must implement it's own execute function

### test.cpp
A preliminary test of the later `execute` functions and the base class's parse function

* `parse()` : inherited from base
* `execute()` : can be changed to fit various tests

### command.h
A class that commands specialize from

* utilizes a vector of strings to determine what valid command is to be invoked
* `Command()` : command constructor
* `execute()` : a self designed function that performs the desired task
* `parse()` : a parse function for use specifically in the command architecture

### connector.h
A class that connectors specialize from

* utilizes two objects of the base class to account for a left and right of the operator
* `Connector (Base*, Base*) : Base()` : connector constructor
* `execute()` : a self designed function that performs the desired task
* `parse()` : a parse function for use specifically in the connector architecture

### exit.cpp
A self designed rshell command to exit the rshell

* `execute()` : a self designed function that exits the rshell
* inherits command defined features

### and.cpp
A class that implements the rshell "&&" connector

* `execute()` : performs the commands according to the and operator
* inherits connector defined features
* must utilize the command class to carry out the commands

### or.cpp
A class that implements the rshell "||" connector

* `execute()` : performs the commands according to the or operator
* inherits connector defined features
* must utilize the command class to carry out the commands

### semi.cpp
A class that implements the rshell ";" connector

* `execute()` : performs the commands according to the semicolon operator
* inherits connector defined features
* must utilize the command class to carry out the commands

## Prototypes/Research

## Development and Testing Roadmap
