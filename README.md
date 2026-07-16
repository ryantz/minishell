*This project has been created as part of the 42 curriculum by ryatan, fkoh.*

# minishell

## Description

`minishell` is a simplified re-implementation of a UNIX shell (a "little
Bash"), written from scratch in C. The goal of the project is to gain
extensive, hands-on knowledge of processes and file descriptors: forking,
executing programs, connecting commands through pipes, redirecting
input/output, handling signals the way an interactive shell does, and
managing an internal environment.

The shell:

- displays a prompt and reads input interactively, with a working history
  (via `readline`)
- parses the input into commands and arguments, respecting single quotes
  (`'...'`, no interpretation) and double quotes (`"..."`, `$` expansion
  still applies)
- searches for and launches the correct executable, using `PATH` or a
  relative/absolute path
- implements redirections `<`, `>`, `>>`, and heredoc `<<`
- implements pipes (`|`), connecting each command's output to the next
  command's input
- expands environment variables (`$VAR`) and `$?` (exit status of the last
  foreground pipeline)
- handles `ctrl-C`, `ctrl-D`, and `ctrl-\` the way `bash` does in
  interactive mode
- implements the built-in commands `echo` (with `-n`), `cd` (relative or
  absolute path), `pwd`, `export`, `unset`, `env`, and `exit`

Signal state is tracked through a single global variable, storing only the
received signal number, so the signal handler never touches the shell's
main data structures directly.

### Bonus

- `&&` and `||` with parentheses for priorities
- Wildcard (`*`) expansion in the current working directory

## Instructions

### Compilation

```sh
make        # builds libft, then compiles minishell
make clean  # removes object files
make fclean # removes object files and the minishell binary
make re     # fclean + full rebuild
```

Requires the `readline` development headers to be installed
(`libreadline-dev` on Debian/Ubuntu-based systems).

### Running

```sh
./minishell
```

```
minishell$ echo hello world
hello world
minishell$ cd /tmp && pwd
/tmp
minishell$ ls -la | grep .c | wc -l
3
minishell$ export FOO=bar
minishell$ echo $FOO
bar
minishell$ cat < input.txt > output.txt
minishell$ exit
exit
```

## Resources

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — used as the reference for expected shell behavior wherever the subject was ambiguous
- [GNU Readline Library documentation](https://tiswww.case.edu/php/chet/readline/readline.html)
- `man` pages for `fork`, `execve`, `pipe`, `dup2`, `waitpid`, `signal`, `sigaction`, `getcwd`, `chdir`, `access`
- [Advanced Programming in the UNIX Environment (Stevens & Rago)](http://www.apuebook.com/) — process control, signals, and file descriptor chapters
- 42 School's Minishell subject PDF

### Use of AI

An AI assistant (Claude) was used throughout the project as a **reviewer and
sounding board**, not as a code generator for core logic. Specifically, it
was used to:

- review already-written functions (env handling, builtins, executor,
  Makefile, lexer/parser) for bugs, memory leaks, and inconsistencies with
  the subject/`bash` reference behavior — e.g. catching a leaked `value` in
  `env_set` on early return, a signature mismatch across the builtin
  dispatch table, and a duplicated source file causing a link conflict
- explain the reasoning behind specific syscalls and design decisions
  (e.g. why `cd` must run in the shell's own process rather than a forked
  child, what `OLDPWD`/`errno`/`env` vs `export -p` semantics are)
- debug a Makefile issue (a stray trailing space in a variable assignment
  silently breaking a build rule)
- discuss trade-offs between implementation approaches (e.g. function-pointer
  dispatch table vs. a plain `if`/`else` chain for builtins) before a design
  decision was made
- help draft this README

All AI-assisted suggestions were reviewed, tested, and understood before
being integrated; the underlying design and the bulk of the implementation
were written independently.
