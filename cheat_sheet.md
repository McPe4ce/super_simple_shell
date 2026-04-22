# Simple Shell - Function Cheat Sheet

## Entry Point

| Function | Purpose |
|----------|---------|
| `main()` | Entry point, calls `run_shell(argv[0])` |

---

## Main Shell Loop (`shell_loop.c`)

### `run_shell(prog_name)`
- **PURPOSE**: Main shell loop - prompts user, reads commands, executes them
- **USES**: `isatty()`, `write()`, `read_line()`, `exec_cmd()`, `free()`
- **RETURNS**: Exit status of last command

---

## Input/Output (`helpers.c`)

### `read_line(bufsize)`
- **PURPOSE**: Reads a single line from stdin with trimmed whitespace
- **USES**: `getline()` - reads line from file descriptor (strips leading/trailing spaces and tabs)
- **RETURNS**: Pointer to trimmed line or NULL on EOF

---

## Command Execution (`helpers.c`)

### `exec_cmd(line, argv, line_num, last_status)`
- **PURPOSE**: Parse and execute a command
- **PROCESS**:
  1. `split_string()` → Parse "command arg1 arg2" into array
  2. Check if builtin (exit, env) → `handle_exit()` or `handle_env()`
  3. `pathfinder()` → Find full path of command
  4. `run_external()` → Fork and execute command
- **RETURNS**: Exit status of command (0-127)
- **NOTES**: Returns 127 if command not found

### `run_external(the_path, args, argv, line_num, line)` [STATIC]
- **PURPOSE**: Fork, execute command, wait for completion
- **PROCESS**:
  1. `fork()` → Create child process
  2. Child (pid==0): `execve()` → Replace process with command
  3. Parent: `waitpid()` → Wait for child and get exit status
- **USES**: `fork()`, `execve()`, `waitpid()`, `WEXITSTATUS()`
- **RETURNS**: Command exit status or 1 (fork failure) or 127 (execve failure)
- **EXITS**: Child process calls `_exit(127)` on execve failure

---

## Command String Parsing (`string_spliter.c`)

### `split_string(str, delimiters)`
- **PURPOSE**: Parse "command arg1 arg2" into array `["command", "arg1", "arg2"]`
- **PROCESS**:
  1. `memcpy()` → Copy string (strtok will modify it)
  2. `strtok(copy, delimiters)` → Extract tokens separated by delimiters
  3. Loop through tokens, count them
  4. Create array of pointers to hold each token
  5. Copy each token individually (tokens persist after original freed)
- **USES**: `malloc()`, `memcpy()`, `strtok()`, `free()`
- **NOTES**:
  - `strtok()` is **DESTRUCTIVE** (modifies input string)
  - That's why we make 2 copies: first to count, second to store
  - Caller must free the array AND each element
- **RETURNS**: Null-terminated array of strings (or NULL if input is NULL)

---

## PATH Resolution (`PATH.c`)

### `pathfinder(cmd)`
- **PURPOSE**: Find full path to executable command (e.g. "ls" → "/bin/ls")
- **PROCESS**:
  1. If cmd contains "/": Check if file exists and is executable
  2. If not: Get PATH environment variable
  3. Split PATH by ":" into directories
  4. For each dir: Build path "dir/cmd" and check if executable
  5. Return first match
- **USES**: `strchr()`, `stat()`, `_getenv()`, `strtok()`, `_strdup()`, `malloc()`
- **MACROS**: `S_IXUSR` → Check if file is executable by user
- **RETURNS**: Malloc'd copy of full path (caller must free) or NULL

### `_getenv(name)`
- **PURPOSE**: Get environment variable value (e.g. "PATH" → "/usr/bin:/bin...")
- **PROCESS**:
  1. Iterate through `environ` array
  2. Match "NAME=" prefix in each entry
  3. Return pointer to value part after "="
- **USES**: `strlen()`, `strncmp()`
- **RETURNS**: Pointer to value or NULL if not found

---

## Built-in Commands (`builtins.c`)

### `handle_exit(args, line, last_status)`
- **PURPOSE**: Exit shell builtin command
- **PROCESS**:
  1. Check if `args[0]` == "exit"
  2. Free resources
  3. `exit(last_status)` → Terminate process with status
- **USES**: `_strcmp()`, `free_exec()`, `free()`, `exit()`
- **NOTES**: This function only returns if NOT exit command

### `handle_env(void)`
- **PURPOSE**: Print all environment variables (env builtin)
- **PROCESS**:
  1. Iterate through extern `environ` array
  2. Write each variable to stdout with `write()`
- **USES**: `write()`, `_strlen()`
- **RETURNS**: 0 (success)

---

## String Utilities (`myfunctions.c`)

### `_strlen(s)`
- **PURPOSE**: Get string length (like strlen but custom)
- **PROCESS**: Count chars until null terminator
- **SAFETY**: Returns 0 if s is NULL
- **RETURNS**: Integer length

### `_strdup(s)`
- **PURPOSE**: Allocate new string and copy contents (like strdup but custom)
- **PROCESS**:
  1. Allocate memory: len + 1 (for null terminator)
  2. Copy all characters using memcpy loop
- **SAFETY**: Returns NULL if malloc fails or input is NULL
- **RETURNS**: Malloc'd copy or NULL

### `_strcmp(s1, s2)`
- **PURPOSE**: Compare two strings (like strcmp but custom)
- **PROCESS**: Compare chars at each index until difference or end
- **RETURNS**: 0 if equal, difference of chars if not

### `_strcat_new(s1, s2)` [DECLARED but NOT USED]
- **PURPOSE**: Concatenate two strings (would return new malloc'd string)
- **NOTE**: Listed in header but implementation not shown

---

## Memory Cleanup

### `free_exec(args, the_path)`
- **PURPOSE**: Free command arguments array and path string
- **PROCESS**:
  1. Free each individual string in args array
  2. Free the args array itself
  3. Free the_path (can be NULL, free() handles it)
- **SAFETY**: Checks if pointers exist before freeing
- **NOTES**: Called after every command execution

---

# Key Concepts & Standard Library Functions

## `strtok(str, delim)`
- **PURPOSE**: Split string by delimiters (spaces, tabs, colons, etc.)
- **EXAMPLE**: `strtok("ls -la", " ")` → "ls", then call again → "-la"
- **⚠️ CRITICAL**: DESTRUCTIVE - modifies input string! Must pass copy or NULL on subsequent calls
- **USAGE**: Command parsing (spaces) & PATH parsing (colons)
- **NOTE**: In this code, two copies made because strtok destroys string

## `WEXITSTATUS(status)` Macro
- **PURPOSE**: Extract real exit code from wait status
- **USED IN**: `run_external()` to get exit status after `waitpid()`
- **EXAMPLE**: `waitpid()` returns encoded status → `WEXITSTATUS()` extracts actual command exit code (0-255)
- **MACRO**: Part of `<sys/wait.h>`

## `st.st_mode` (from struct stat)
- **PURPOSE**: File mode - contains file permissions and type info
- **BITFIELD**: Stores permissions as bit flags
- **COMMON MACROS**:
  - `S_IXUSR` → Is file executable by owner? `(st.st_mode & S_IXUSR)`
  - `S_ISDIR` → Is it a directory?
  - `S_ISREG` → Is it a regular file?
- **USAGE**: Checking if command file is executable in `pathfinder()`

## `stat(path, &st)`
- **PURPOSE**: Get file information (permissions, size, timestamps, etc.)
- **RETURN**: 0 if successful, -1 if file doesn't exist
- **USAGE**: Check if file exists AND check if executable (st_mode)
- **USED IN**: `pathfinder()` to verify commands

## `getline(&line, &bufsize, stdin)`
- **PURPOSE**: Read entire line from file descriptor (handles buffer auto-growth)
- **USAGE**: Read command from user
- **RETURN**: Number of chars read, or -1 on EOF
- **FEATURES**: Auto-allocates memory, handles large lines

## `fork()`
- **PURPOSE**: Create child process (duplicates current process)
- **PARENT**: Returns child's PID
- **CHILD**: Returns 0
- **USAGE**: Create process to execute external command

## `execve(path, args, environ)`
- **PURPOSE**: Replace current process with new command
- **ARGS**:
  - `path` = full path to executable
  - `args` = command + arguments
  - `environ` = environment variables
- **⚠️ CRITICAL**: Only called in CHILD process (after fork)
- **RETURN**: -1 on error (never returns on success, process is replaced)
- **USAGE**: Execute actual command in child process

## `waitpid(pid, &status, 0)`
- **PURPOSE**: Parent waits for child process to finish
- **RETURNS**: Child's PID on success
- **STATUS**: Encoded exit info (must use `WEXITSTATUS()` to extract)
- **USAGE**: Parent waits for executed command to complete

## `isatty(fd)`
- **PURPOSE**: Check if file descriptor is connected to terminal
- **USAGE**: Only show prompt if input is interactive (not piped)
- **EXAMPLE**: `echo 'ls' | ./shell` → no prompt. Direct typing → prompt

---

# Execution Flow Diagram

```
User types: "ls -la"
    ↓
run_shell() → shows "$ " prompt
    ↓
read_line() → returns "ls -la" (trimmed)
    ↓
exec_cmd()
    ├→ split_string() → ["ls", "-la", NULL]
    ├→ _strcmp(args[0], "exit") → not exit
    ├→ _strcmp(args[0], "env") → not env
    ├→ pathfinder("ls")
    │   ├→ _getenv("PATH") → "/usr/bin:/bin:..."
    │   ├→ strtok() → split by ":"
    │   ├→ stat("/usr/bin/ls") + (st.st_mode & S_IXUSR)
    │   └→ return "/usr/bin/ls"
    └→ run_external("/usr/bin/ls", ["ls", "-la", NULL], ...)
        ├→ fork()
        ├→ Child: execve("/usr/bin/ls", ["ls", "-la", NULL], environ)
        ├→ Parent: waitpid(child_pid, &status, 0)
        ├→ WEXITSTATUS(status)
        └→ free_exec() → cleanup memory
    ↓
return exit status → loop back to top
```

---

# Memory Management

## ALLOCATED (caller must free)
- `split_string()` → array of strings
- `_strdup()` → duplicated string
- `pathfinder()` → full path string
- `read_line()` → input line

## FREED BY
- `free_exec()` → args array + individual strings + path
- `run_shell()` → input line
- `exec_cmd()` → args array (via `free_exec()`)

---

# Error Codes & Return Values

| Value | Meaning |
|-------|---------|
| `0` | Success |
| `1` | `fork()` failed |
| `127` | Command not found or `execve()` failed |
| `Other` | Command's actual exit status |
| `2` | Typically for shell syntax errors (not used here) |

