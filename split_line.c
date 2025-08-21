#include "hsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * split_line - Tokenizes a command line into arguments
 * @line: Input command line
 * Return: Array of argument strings
 */
char **split_line(char *line)
{
    int bufsize = 64, i = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token, **tmp;

    if (!tokens)
        return NULL;

    token = strtok(line, " \t\r\n\a");
    while (token != NULL)
    {
        tokens[i++] = token;

        if (i >= bufsize)
        {
            bufsize += 64;
            tmp = realloc(tokens, bufsize * sizeof(char *));
            if (!tmp)
            {
                free(tokens);
                return NULL;
            }
            tokens = tmp;
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[i] = NULL;
    return tokens;
}
