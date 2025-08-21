#include "hsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/**
 * execute_command - Forks and executes a command safely
 * @args: Argument array
 * @prog_name: Program name (for errors)
 * @line_count: Line number (for errors)
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
	pid_t pid;
	int status;

	if (!args || !args[0])
		return (0);

	cmd_path = get_path(args[0]);
	if (!cmd_path) /* not found -> no fork, print error, return 127 */
	{
		print_error(prog_name, line_count, args[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (1);
	}

	if (pid == 0) /* child */
	{
		execve(cmd_path, args, environ);
		/* If execve returns, it's an error. Decide a sensible status. */
		if (errno == EACCES)
			_exit(126);
		/* Match sh behavior: not found already filtered, so generic failure */
		_exit(126);
	}

	/* parent */
	waitpid(pid, &status, 0);
	free(cmd_path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		/* Map signal to 128+signal (common shell convention) */
		return (128 + WTERMSIG(status));
	return (1);
}
