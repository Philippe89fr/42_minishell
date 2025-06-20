## Minishell - 42

# Description:
Minishell is a project that recreates the functionality of a basic UNIX shell, similar to bash--posix. The program implements a command-line interpreter that can parse, execute, and manage user commands in an interactive environment. The shell supports command execution, built-in commands, input/output redirections, pipes, environment variable expansion, and signal management, offering a comprehensive learning of how bash works.

The minishell program provides an interactive prompt where users can:
- Execute commands found in PATH or using relative/absolute paths
- Use built-in commands (echo, cd, pwd, export, unset, env, exit)
- Handle input/output redirections (<, >, <<, >>)
- Create command pipelines using pipes (|)
- Expand environment variables (VAR)
- Navigate command history and handle interactive signals (Ctrl-C, Ctrl-D, Ctrl-)

The program also mimics bash behavior for command execution, quoting mechanisms (single and double quotes), and interactive shell features.

# Context:
Part of 42 Common Core.

# Main Technologies / Skills Used:

- **Programming Languages:** C
- **Process Management:** fork(), wait(), waitpid(), execve() for command execution
- **Inter-Process Communication:** Pipes for connecting command input/output
- **File Descriptors:** dup(), dup2() for input/output redirection
- **Signal Handling:** sigaction(), signal() for interactive shell behavior (Ctrl-C, Ctrl-D, Ctrl-)
- **System Calls:** File operations (open, read, write, close), directory operations (opendir, readdir, closedir)
- **Memory Management:** Dynamic allocation for command parsing and environment handling
- **String Processing / tokenization:** Command parsing, and quote handling
- **Environment Variables:** getenv(), environment manipulation and expansion
- **Error Handling:** Comprehensive error management for system calls and invalid commands
- **Makefile Management:** For automating project compilation with proper linking

# Installation and compilation
1. Clone this repository into your project:
```bash
git clone git@github.com:Philippe89fr/42_minishell.git
```
2. Run the following command:
```bash
make bonus
```
3. To use the program, run the program and then enter any bash--posix usual command line:
```bash
./minishell
```
