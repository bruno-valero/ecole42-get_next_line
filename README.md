
# get_next_line

This project is part of the 42 curriculum and aims to create a function that returns, on each call, one line read from a file descriptor. It is an excellent opportunity to practice controlled file reading, the use of buffers, and static variables in C.

---

## 📚 Objective

Implement the function `get_next_line()` capable of returning the next available line from a file descriptor, correctly preserving the state between successive calls. The return must include the newline character `\n`, except at the end of the file.

---

## 🚫 Restrictions

- **Use of [`libft`](https://github.com/bruno-valero/ecole42-libft) is forbidden.** No external custom functions may be used.
- Only the functions **`read`**, **`malloc`**, and **`free`** are allowed.
- **Global variables are prohibited.**
- **`lseek()` is forbidden.**

---

## ✅ Mandatory Part

The function must have the following prototype:

```c
char *get_next_line(int fd);
```

* Must work with any valid file descriptor.
* Must read and return one line per call.
* Must return `NULL` in case of error or end of file.
* The project must be compilable with:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=<n> get_next_line.c get_next_line_utils.c
```

---

## 🔁 Bonus Part

The bonus version of the project was **successfully implemented** and includes:

* Support for multiple file descriptors simultaneously.
* Use of **only one static variable** per call.
* Modular structure, with the following additional files:

```text
get_next_line_bonus.c
get_next_line_bonus.h
get_next_line_utils_bonus.c
```

To compile the bonus:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=<n> get_next_line_bonus.c get_next_line_utils_bonus.c
```

---

## 🧪 Usage Example

```c
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

---

## 📝 Considerations

* The project was implemented with a focus on performance and readability.
* Memory management was carefully handled to avoid leaks and undefined behavior.
* Tested with different `BUFFER_SIZE` values, including `1`, `42`, `9999`, and `1000000`.

---

## ✅ Status

- [x] Mandatory part completed
- [x] Bonus part completed
- [x] Validation with multiple file descriptors
- [x] Validation with standard input (stdin)