# Simple Shell

A UNIX command line interpreter written in C.  
This project is a basic implementation of a shell that can execute commands, handle paths, and provide built-in commands like `exit` and `env`.

---

## Features

- Displays a prompt and waits for user input.
- Executes simple commands with or without arguments.
- Handles the `PATH` variable to locate executables.
- Provides built-in commands:
  - `exit` — exits the shell.
  - `env` — prints the current environment.
- Works in both **interactive** and **non-interactive** modes.
- Handles end of file (Ctrl+D).
- Produces error messages in the same format as `/bin/sh`.

---

## Requirements

- Ubuntu 20.04 LTS
- `gcc` compiler with the following options:
```bash
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

---

## Usage

### Interactive mode

```bash
$ ./hsh
($) /bin/ls
file1 file2 file3
($) exit
```

### Non-interactive mode

```bash
$ echo "/bin/ls" | ./hsh
file1 file2 file3
```

---

## Files

* `main.c` — entry point of the program.
* `execute_command.c` — executes commands using `fork` and `execve`.
* `split_line.c` — splits input lines into tokens.
* `get_path.c` — handles path resolution for commands.
* `utils.c` — helper functions.
* `hsh.h` — header file with function prototypes.
* `man_simple_shell` — manual page for the shell.

---

## Compilation

To build the shell:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

---

## Testing

Run in interactive mode:

```bash
./hsh
```

Run in non-interactive mode:

```bash
echo "ls -l" | ./hsh
```

---

## Author

- Alba Eftimi [@abfabs](https://github.com/abfabs)

```