# GuiarStr

## Why GuiarStr?

GuiarStr helps C programmers handle strings more easily.

C has very basic string support. GuiarStr adds useful functions like trim, split, replace, lowercase, and uppercase — all without external dependencies.

It’s lightweight, easy to use, and perfect for beginners, embedded systems, CLI tools, or any C project that needs better string handling.


                            ------------------------------

## ✨ Features

- `guiarstr_trim` – Removes leading and trailing whitespace.
- `guiarstr_split` – Splits a string into parts based on a given delimiter.
- `guiarstr_replace` – Replaces all occurrences of a substring with another.
- `guiarstr_tolower` – Converts a string to lowercase (in-place).
- `guiarstr_toupper` – Converts a string to uppercase (in-place).

---

## 📦 Installation

### Option 1: Using `make`

```bash
make           # Builds the static library (libguiarstr.a)
make test      # Builds and runs the test suite
  
                           -----------------------------

🧪 Example Usage

#include <stdio.h>
#include "guiarstr.h"

int main() {
    char text[] = "  Hello World  ";
    printf("Trimmed: '%s'\n", guiarstr_trim(text));

    size_t count;
    char** parts = guiarstr_split("one,two,three", ',', &count);
    for (size_t i = 0; i < count; ++i) {
        printf("Part %zu: %s\n", i + 1, parts[i]);
    }
    guiarstr_split_free(parts, count);

    return 0;
}

                              -------------------------------
                              
📁 Project Structure

guiarstr/
├── include/        # Public header(s)
│   └── guiarstr.h
├── src/            # Implementation
│   └── guiarstr.c
├── tests/          # Unit tests
│   └── main.c
├── examples/       # Example programs (optional)
├── CMakeLists.txt  # CMake build file (optional)
├── Makefile        # Makefile for building and testing
├── README.md       # This file
└── LICENSE         # License information

  
                              ------------------------------
                              
📄 License

This project is licensed under the MIT License.
Copyright (c) GUIAR OQBA
See LICENSE for details.

                             -------------------------------
📫 Author

GUIAR OQBA
Email: techokba@gmail.com
Website: https://okba14.github.io
Phone: +2136-71-36-04-38


                              
