#include "hsh.h"
#include <stdio.h>
#include <string.h>

/**
 * print_error - Prints an error message like sh
 * @prog_name: Program name
 * @line_count: Line number
 * @cmd: Command not found
 */
void print_error(char *prog_name, int line_count, char *cmd)
{
	fprintf(stderr, "%s: %d: %s: not found\n", prog_name, line_count, cmd);
}

/**
 * builtin_env - Prints all environment variables
 */
void builtin_env(void)
{
	int i = 0;

	while (environ && environ[i])
		printf("%s\n", environ[i++]);
}

/**
 * _getenv - Gets environment variable value using environ
 * @name: variable name
 * Return: pointer to value within environ, or NULL
 */
char *_getenv(const char *name)
{
	size_t nlen;
	int i;

	if (!name || !environ)
		return (NULL);

	nlen = strlen(name);
	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, nlen) == 0 && environ[i][nlen] == '=')
			return (environ[i] + nlen + 1);
	}
	return (NULL);
}
