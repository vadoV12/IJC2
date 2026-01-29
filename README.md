# IJC – Homework 2 (DU2)

Solution of **Homework 2** for the course **IJC (C Programming Language)** at FIT VUT.

The assignment consists of two independent parts:
1. Implementation of a simplified `tail` utility using a circular buffer.
2. Rewriting a C++ word-frequency program into ISO C using a custom hash table library.

---

## Part 1 – tail

### Description

The program `tail.c` prints the last *N* lines of a text file.

- If no file is specified, input is read from `stdin`
- Default behavior prints the last **10 lines**
- Option `-n <number>` prints the last `<number>` lines
- Error messages are printed to `stderr`

The output behavior is similar to the POSIX `tail` command.

### Features

- Circular buffer for dynamically allocated lines
- Fixed implementation limit on line length (e.g. 4095 characters)
- Lines exceeding the limit are truncated
- The first truncation produces a warning on `stderr`

## Part 2 – maxwordcount

### Description

The program `maxwordcount` reads text from standard input and prints
all words with the **maximum occurrence count**.

This program is an ISO C rewrite of a C++ implementation using
`std::unordered_map`.  
Instead of STL containers, a **custom hash table library (`htab`)**
is used.

---

### Program Behavior

- Input is read from `stdin`
- A word is defined as a sequence of characters separated by whitespace
- Words longer than the given limit are truncated
- A warning about truncation is printed **at most once**
- Output order is not specified
