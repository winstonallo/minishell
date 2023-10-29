# minishell

🚧🚧WORK IN PROGRESS🚧🚧

This project aims to emulate a shell. Note that this is not a standalone shell, it has access to a parent shell
to run commands, the main task here is command line parsing.

The base principle is:
1. Initialize environment data
2. Initialize lists
3. Give the prompt to user
4. Read user input
5. Process user input
    
    a.Check valdidity/parse (both part of the same process)
    
    b.Execute

6. Free allocated memory (except for environment data)
7. Go back to nr.2

## MAIN LOOP

Get the input from the readline function,
parse/execute, give prompt back.
On startup, clear the terminal to give
the feeling of starting a new program.

add_history: allows to go back on previously entered input using the up/down arrows

### a.Parse for quotes

Go through the command line and store each dquote/squote/uquote sequence in a list setting the flags accordingly and removing the unescaped
quotes in the process.

### b.Expand

Look for expandable arguments ($arg) and replace them with their values.
Here expanding unquoted sequences is simple since they are already split by words, quoted sequences is a bit trickier since you have to split them into words based on '$' characters.

### c.Process Escapes

Look for escape characters in double-/unquoted sequences, remove them and write the escaped character.

### d.Parse special characters

Look for pipes, input/output redirections and create a new list of sequences taking those into account, removing them from the strings and setting flags accordingly.

### e.Get command table

Create a new list, with this time an array of strings in each node (since execve takes it as an argument), look for input/output redirections, open the files they point to and store their file descriptors in the list.
