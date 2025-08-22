#include "hsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * try_direct_path - Checks if command includes '/' and is executable
 * @cmd: Command string
 *
 * Return: Duplicated path string if executable, NULL otherwise
 */
static char *try_direct_path(char *cmd)
{
	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

/**
 * search_in_path - Searches PATH directories for a command
 * @cmd: Command string
 * @path_env: PATH environment variable
 *
 * Return: Full path string if found, NULL otherwise
 */
static char *search_in_path(char *cmd, char *path_env)
{
	char *path_dup, *dir, *full_path;
	size_t len;

	path_dup = strdup(path_env);
	if (!path_dup)
		return (NULL);

	dir = strtok(path_dup, ":");
	while (dir)
	{
		len = strlen(dir) + 1 + strlen(cmd) + 1;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_dup);
			return (NULL);
		}

		snprintf(full_path, len, "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_dup);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_dup);
	return (NULL);
}

/**
 * get_path - Resolves the full path of a command using PATH
 * @cmd: Command name
 *
 * Return: Full path string (malloc'ed) or NULL
 */
char *get_path(char *cmd)
{
	char *path_env, *resolved;

	if (!cmd)
		return (NULL);

	resolved = try_direct_path(cmd);
	if (resolved)
		return (resolved);

	path_env = _getenv("PATH");
	if (!path_env || path_env[0] == '\0')
		return (NULL);

	return (search_in_path(cmd, path_env));
}
