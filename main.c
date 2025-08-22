#include "hsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * handle_exit - Handles the "exit" builtin
 * @args: Argument array
 * @line: Input line buffer
 * @last_status: Exit code to use
 */
static void handle_exit(char **args, char *line, int last_status)
{
	free(args);
	free(line);
	exit(last_status);
}

/**
 * handle_env - Handles the "env" builtin
 * @args: Argument array
 */
static void handle_env(char **args)
{
	builtin_env();
	free(args);
}

/**
 * process_line - Tokenizes and executes a single line of input
 * @line: Command line input
 * @argv: Program name vector
 * @line_count: Current line number
 * @last_status: Pointer to last command status
 */
static void process_line(char *line, char **argv,
		int line_count, int *last_status)
{
	char **args;

	if (line[0] == '\0')
		return;

	args = split_line(line);
	if (!args || !args[0])
	{
		free(args);
		return;
	}

	if (strcmp(args[0], "exit") == 0)
		handle_exit(args, line, *last_status);

	if (strcmp(args[0], "env") == 0)
	{
		handle_env(args);
		*last_status = 0;
		return;
	}

	*last_status = execute_command(args, argv[0], line_count);
	free(args);
}

/**
 * main - Entry point for the shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: last command status
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int line_count = 0, last_status = 0;

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
		process_line(line, argv, line_count, &last_status);
	}

	free(line);
	return (last_status);
}
