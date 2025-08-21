#include "hsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * main - Entry point for the shell
 * @argc: argument count
 * @argv: argument vector
 * Return: last command status
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int line_count = 0;
	char **args;
	int last_status = 0;

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ "), fflush(stdout);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				putchar('\n');
			break;
		}

		line_count++;
		line[nread - 1] = '\0';
		if (line[0] == '\0')
			continue;

		args = split_line(line);
		if (!args || !args[0])
		{
			free(args);
			continue;
		}

		if (strcmp(args[0], "exit") == 0)
		{
			int code = last_status;

			free(args);
			free(line);
			exit(code);
		}

		if (strcmp(args[0], "env") == 0)
		{
			builtin_env();
			free(args);
			last_status = 0;
			continue;
		}

		last_status = execute_command(args, argv[0], line_count);
		free(args);
	}

	free(line);
	return (last_status);
}
