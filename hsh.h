#ifndef HSH_H
#define HSH_H

extern char **environ;

char **split_line(char *line);
char *get_path(char *cmd);
int execute_command(char **args, char *prog_name, int line_count);
void print_error(char *prog_name, int line_count, char *cmd);
void builtin_env(void);
char *_getenv(const char *name);

#endif
