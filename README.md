# CS 100 Programming Project
> Winter 2020 - Alejandro Sherman (862062898) and Eddie...

## Introduction
Our project is the implementation of a basic command shell, complete with a user interface, and functionality of certain commands and connectors. The shell will allow for the use of standard commands after they are input by a user, such as `exit`, as well as the use of three connectors that allow users to execute multiple commands at once. These connectors are "||" (or), "&&" (and), and ";" (semi). The composite design pattern will be utilized to implement the commands and the connectors. The project will be created in C++ and features will be implemented using C++ classes.

## Diagram

## Classes
### user.cpp
The area that the user interacts with when they use the shell

* displays the command prompt `guest@rshell:~$`
* takes the user input and sends it where it needs to go

### base.h
A class function that other frameworks build off of

* comprised of virtual functions as the class is meant to be used as a superclass
* `parse()` : parses user input using tokens
* `execute()` : returns a boolean true or false depending on if a command executes properly


## Prototypes/Research

## Development and Testing Roadmap
