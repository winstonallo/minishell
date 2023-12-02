# minishell

## 42 uni project

This project is about writing a simple shell.

## Tasks

### Command line parsing

src/parser

Make the command line executable by:

  -Splitting the command line based on quotes and spaces
  
  -Looking for special operators and removing them from the command line
  
  -Expanding environment variables
 
  -Creating an array that we can pass to execve

### Lexical analysis

src/lexer

  -Check for syntax errors (special operators at end of line/next to each other/unclosed quotes, etc)

### Command line executing

src/executer

  -Set redirections, pipes, check for missing files/invalid permissions/nonexisting commands, etc
 
  -Execute command, get exit code of last execution

### Built ins

src/builtins

  -The subject requires us to write some commands ourselves (the rest of them are being run through the parent shell):
  
    echo (-n)
    
    cd
    
    pwd
    
    export
    
    unset
    
    exit
    
    env

grade: 99/100 - program exits with wrong exit code (127) when limiting max resources
