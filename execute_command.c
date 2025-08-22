#include "hsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

/**
 * fork_and_exec - Handles forking and execve call
 * @cmd_path: Full path to the command
 * @args: Argument array
 *
 * Return: Exit status code
 */
static int fork_and_exec(char *cmd_path, char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (1);
	}

	if (pid == 0)
	{
		execve(cmd_path, args, environ);
		if (errno == EACCES)
			_exit(126);
		_exit(126);
	}

	waitpid(pid, &status, 0);
	free(cmd_path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

/**
 * execute_command - Forks and executes a command safely
 * @args: Argument array
 * @prog_name: Program name (for errors)
 * @line_count: Line number (for errors)
 *
 * Return: exit status to propagate (0..255)
 *
 * Conventions:
 *  - 127: command not found (no PATH match, PATH unset/empty)
 *  - 126: found but not executable (execve failed with EACCES)
 *  - else: child's exit status
 */
int execute_command(char **args, char *prog_name, int line_count)
{
	char *cmd_path;

	if (!args || !args[0])
		return (0);

	cmd_path = get_path(args[0]);
	if (!cmd_path)
	{
		print_error(prog_name, line_count, args[0]);
		return (127);
	}

	return (fork_and_exec(cmd_path, args));
}
