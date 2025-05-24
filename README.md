# Get Next Line - Milestone 1 Common-Core project

This project focused on implementing a function capable of reading a file line by line, handling file descriptors and memory efficiently in C. It was a practical opportunity to deepen the understanding of low-level input/output operations, buffer management, and string handling without using standard C library functions like `getline`.

## Goal

Implement a function called `get_next_line` that returns the next line from a file descriptor, one line at a time. It must work with any file descriptor, including standard input, and handle multiple file descriptors simultaneously.

## Key Requirements
- Must return the next line from a file, ending in \n or EOF.

- Must manage buffers and memory allocation manually.

- Must work with multiple file descriptors (bonus).

- Should avoid memory leaks and ensure efficient resource management.

- Return NULL when EOF is reached and no data remains.

## Concepts Learned
- **File descriptor** handling and reading from files in C using read().

- Efficient use of **buffers**, **dynamic memory**, and **string manipulation**.

- Use of **static variables** to preserve state between function calls.

- Understanding how to manage multiple file descriptors at once.

- Careful **resource management** to avoid memory leaks and undefined behavior.
