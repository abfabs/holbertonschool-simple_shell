#ifndef HSH_H
#define HSH_H

#include <stddef.h>

/* Global environment */
extern char **environ;

/* Built-ins */
void builtin_env(void);

/* Command execution */
int execute_command(char **args, char *prog_name, int line_count);

/* PATH resolution */
char *get_path(char *cmd);
char *_getenv(const char *name);

/* Input parsing */
char **split_line(char *line);

#endif /* HSH_H */
