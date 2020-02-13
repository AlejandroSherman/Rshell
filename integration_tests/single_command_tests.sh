#!/bin/bash

echo "Executing ../rshell ls"
../rshell "ls"
echo "Executing ../rshell echo hello"
../rshell "echo hello"
echo "Executing ../rshell git status"
../rshell "git status"
echo "Executing ../rshell echo "hi" # && bye"
../rshell "echo hi # && bye"
echo "Executing ../rshell ls -a"
../rshell "rm -f blah"
echo "Executing ../rshell "
../rshell "exit"
