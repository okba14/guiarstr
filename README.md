# GuiarStr – Advanced String Manipulation Library for C

[![Version](https://img.shields.io/badge/version-1.3.0-blue.svg)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Build & Test](https://github.com/okba14/guiarstr/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/okba14/guiarstr/actions/workflows/c-cpp.yml)
[![UTF-8 Support](https://img.shields.io/badge/UTF--8-Full%20Support-orange.svg)](#)
![Language](https://img.shields.io/badge/Language-C-blue)
![Platforms](https://img.shields.io/badge/Platforms-Linux%20%7C%20macOS%20%7C%20Windows-orange)
[![SLSA Level 3 Provenance](https://img.shields.io/badge/SLSA-Level%203-blueviolet.svg)](https://slsa.dev)


---

## 🚀 Why GuiarStr?

**GuiarStr** is a comprehensive, professional-grade string manipulation library for **C programmers**.  
While C has very basic string support, GuiarStr provides a **rich set of modern string operations** with:

- Dynamic strings
- Unicode/UTF-8 support
- Memory safety
- Efficient performance

Perfect for **embedded systems** to **complex multilingual software** — without external dependencies.

---

## ✨ Features

### 📝 Core String Operations

| Function | Description |
|----------|-------------|
| `guiarstr_trim` | Removes leading and trailing whitespace. |
| `guiarstr_strip` | Removes specified characters from both ends. |
| `guiarstr_tolower` / `guiarstr_toupper` | Converts string to lowercase/uppercase (in-place). |
| `guiarstr_reverse` | Reverses a string (**UTF-8 safe**). |
| `guiarstr_replace` | Replaces all occurrences of a substring. |
| `guiarstr_replace_n` | Replaces with a limit on replacements. |
| `guiarstr_replace_char` | Replaces all occurrences of a character. |
| `guiarstr_remove_chars` | Removes all specified characters. |

---

### 🔍 Advanced Search & Inspection

- `guiarstr_starts_with` / `guiarstr_ends_with` – Prefix/suffix checking.
- `guiarstr_starts_withi` / `guiarstr_endswithi` – Case-insensitive variants.
- `guiarstr_contains` – Checks if a string contains a substring.
- `guiarstr_count` – Counts occurrences of a substring.
- `guiarstr_find` / `guiarstr_rfind` – Find substring positions.
- `guiarstr_find_char` / `guiarstr_rfind_char` – Find character positions.
- `guiarstr_find_any` / `guiarstr_find_not_any` – Advanced character search.

---

### 🔗 Split & Join Operations

- `guiarstr_split` – Splits by character delimiter.
- `guiarstr_split_str` – Splits by string delimiter.
- `guiarstr_split_any` – Splits by any of multiple delimiters.
- `guiarstr_split_lines` – Splits by line endings (handles `\n`, `\r\n`).
- `guiarstr_join` – Joins string array with separator.
- `guiarstr_join_views` – Joins string views efficiently.

---

### 📌 Dynamic Strings (GuiarStr)

- `guiarstr_create` – Creates a dynamic string.
- `guiarstr_append` – Appends to a dynamic string.
- `guiarstr_insert` – Inserts at a specific position.
- `guiarstr_remove` – Removes a range of characters.
- `guiarstr_reserve` – Pre-allocates memory.
- `guiarstr_resize` – Resizes with fill character.
- `guiarstr_shrink_to_fit` – Optimizes memory usage.

---

### 🏗 String Builder (GuiarStrBuilder)

- `guiarstr_builder_create` – Creates an efficient string builder.
- `guiarstr_builder_append` – Appends strings efficiently.
- `guiarstr_builder_append_fmt` – Appends formatted strings.
- `guiarstr_builder_build` – Builds the final string.

---

### 🌍 Unicode/UTF-8 Support

- `guiarstr_utf8_len` – Gets UTF-8 character count.
- `guiarstr_utf8_char_len` – Gets byte length of a UTF-8 character.
- `guiarstr_utf8_byte_pos` – Converts character position to byte position.
- `guiarstr_utf8_validate` – Validates UTF-8 sequences.
- `guiarstr_utf8_width` – Gets display width for monospace fonts.
- `guiarstr_utf8_substring` – Extracts UTF-8 substring.

✅ **Handles emojis, Arabic, and all Unicode characters correctly**.

---

### 🔢 Number Conversion

- `guiarstr_to_int` / `guiarstr_from_int`
- `guiarstr_to_double` / `guiarstr_from_double`
- `guiarstr_to_long` / `guiarstr_from_long`  
✔ Includes **error handling**.

---

### 🖋 Formatting

- `guiarstr_printf` – Creates formatted strings.
- `guiarstr_append_printf` – Appends formatted strings to dynamic strings.

---

### 📂 File Operations

- `guiarstr_read_file` – Reads entire file into a string.
- `guiarstr_write_file` – Writes string content to file.

---

### 🛡 Error Handling

- Comprehensive error codes with descriptive messages.
- All functions return error status for safe operation.
- `guiarstr_error_message` – Gets human-readable error descriptions.

---

## 🧠 UTF-8 Aware

- Fully UTF-8 aware operations.
- Works perfectly for multilingual apps and terminal-based UIs.
- Supports **byte-level** and **character-level** manipulation.

---

## 📦 Installation

### **Option 1: Build locally**

```bash
make            # Builds static lib (libguiarstr.a) + shared lib (libguiarstr.so)
make test       # Runs the test suite
make example    # Builds usage demo
Option 2: Install

make install PREFIX=$HOME/.local
This installs:

guiarstr.h → $PREFIX/include

libguiarstr.a and libguiarstr.so → $PREFIX/lib

guiarstr.pc → $PREFIX/lib/pkgconfig

Option 3: Using CMake

mkdir build && cd build
cmake ..
make
sudo make install

🧪 Example Usage
Basic Operations

#include <stdio.h>
#include "guiarstr.h"

int main() {
    char text[] = "  Hello World  ";
    printf("Trimmed: '%s'\n", guiarstr_trim(text));

    size_t count;
    char** parts = guiarstr_split_str("oneXYZtwoXYZthree", "XYZ", &count);
    for (size_t i = 0; i < count; ++i) {
        printf("Part %zu: %s\n", i + 1, parts[i]);
    }
    guiarstr_split_free(parts, count);

    char* reversed = guiarstr_reverse("okba😊dev");
    printf("Reversed: %s\n", reversed);
    free(reversed);
}
Dynamic Strings

#include "guiarstr.h"

int main() {
    GuiarStr* str = guiarstr_create("Hello");
    guiarstr_append(str, " World");
    guiarstr_append_char(str, '!');
    guiarstr_insert(str, 5, " there");

    printf("Dynamic string: '%s'\n", str->data);

    guiarstr_free(str);
}
String Builder

#include "guiarstr.h"

int main() {
    GuiarStrBuilder* builder = guiarstr_builder_create(16);
    guiarstr_builder_append(builder, "The answer is: ");
    guiarstr_builder_append_fmt(builder, "%d", 42);

    GuiarStr* result = guiarstr_builder_build(builder);
    printf("Built: '%s'\n", result->data);

    guiarstr_free(result);
    guiarstr_builder_free(builder);
}
Unicode Operations

#include "guiarstr.h"

int main() {
    const char* text = "مرحبا 😊";
    printf("UTF-8 length: %zu characters\n", guiarstr_utf8_len(text));
    printf("Byte length: %zu bytes\n", strlen(text));
    printf("Display width: %zu columns\n", guiarstr_utf8_width(text));

    char* substr = guiarstr_utf8_substring(text, 2, 2);
    printf("Substring [2:4]: '%s'\n", substr);
    free(substr);
}
🔧 Using with pkg-config

gcc main.c $(pkg-config --cflags --libs guiarstr) -o app
Make sure PKG_CONFIG_PATH is set if installed to a custom location:
export PKG_CONFIG_PATH=$HOME/.local/lib/pkgconfig

📁 Project Structure
makefile

guiarstr/
├── include/              # Public headers
│   └── guiarstr.h
├── src/                  # Implementation
│   └── guiarstr.c
├── tests/                # Tests
│   └── main.c
├── examples/             # Example programs
│   └── usage.c
├── assets/               # Images
│   └── build_and_test.png
├── CMakeLists.txt
├── guiarstr.pc
├── guiarstr.pc.in
├── Makefile
├── README.md
├── CHANGELOG.md
└── LICENSE

📄 License
Licensed under the MIT License
© GUIAR OQBA

📫 Author
👤 Name: GUIAR OQBA
📧 Email: techokba@gmail.com
🌐 ORCID: 0009-0008-1629-0002
💼 LinkedIn: guiar-oqba
💻 GitHub: okba14
📚 Zenodo: 15786076
📝 Hashnode: @okba
✈️ Telegram: @okba_elkantara
📱 Phone: +2136-71-36-04-38

🔄 Version History
See CHANGELOG.md for release notes.

🤝 Contributing
Contributions are welcome! Please feel free to submit a Pull Request.

Fork the repository
Create your feature branch (git checkout -b feature/amazing-feature)
Commit your changes (git commit -m 'Add some amazing feature')
Push to the branch (git push origin feature/amazing-feature)
Open a Pull Request.

