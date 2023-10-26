# minishell

## 🚧🚧WORK IN PROGRESS🚧🚧

This project aims to emulate a shell. Note that this is not a standalone shell, it has access to a parent shell
to run commands, the main task here is command line parsing.

## STEP 1: PARSING

### a.Parse for quotes

Go through the command line and store each dquote/squote/uquote sequence in a list with a flag, removing the
quotes in the process, (except the escaped ones).

### b.Expand

Look for expandable arguments ($arg) and replace them with their values.

