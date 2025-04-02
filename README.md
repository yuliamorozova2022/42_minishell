# Custom Shell in C

This project involves implementing a shell using the C programming language.

## Features

### ✅ Basic Functionality
- Displays a **prompt** when waiting for a new command.
- Maintains a **command history**.
- Searches and executes the correct program based on:
  - The `PATH` environment variable.
  - A relative or absolute path.

### ✅ Input Handling
- Properly handles **single quotes (`'`)** to prevent interpretation of metacharacters.
- Properly handles **double quotes (`"`)**, allowing `$` (dollar sign) expansion.
- Does **not** interpret:
  - Unclosed quotes.
  - Special characters such as backslash (`\`) or semicolon (`;`).

### ✅ Redirections
- **Input redirection (`<`)** – Reads input from a file.
- **Output redirection (`>`)** – Writes output to a file.
- **Append redirection (`>>`)** – Writes output to a file in append mode.
- **Heredoc (`<<`)** – Reads input until a given delimiter is encountered (without updating history).

### ✅ Pipes
- Supports the **pipe (`|`)** operator to connect the output of one command to the input of the next.

### ✅ Environment Variables
- Expands **environment variables** (`$VAR`).
- Expands **`$?`** to return the exit status of the last executed command.

### ✅ Signal Handling
- Uses **only one global variable** for signal handling.
- **Does not allow** signal handlers to modify main data structures.

### ✅ Keyboard Shortcuts (Interactive Mode)
| Shortcut | Behavior |
|----------|----------|
| `Ctrl + C` | Displays a new prompt on a new line. |
| `Ctrl + D` | Exits the shell. |
| `Ctrl + \` | Does nothing (default behavior). |

### ✅ Built-in Commands
The shell includes the following built-in commands:
- **`echo`** (with `-n` option)
- **`cd`** (only with a relative or absolute path)
- **`pwd`** (no options)
- **`export`** (no options)
- **`unset`** (no options)
- **`env`** (no options or arguments)
- **`exit`** (no options)

---

🚀 **This shell provides a simplified Bash-like experience, handling essential command execution, redirections, pipes, and built-ins efficiently.**
