# minishell functions

## input

### readline (const char *prompt)

Reads a line from the terminal, using prompt as a prompt, removing the final newline. Returned line is malloced(!!), caller must free it. Allows to edit the line while typing (emacs style by default, vi also available)