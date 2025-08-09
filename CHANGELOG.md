# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/).

## [1.3.0] - 2025-08-09

### Added
- Dynamic string structure (GuiarStr) with automatic memory management
- String view structure (GuiarStrView) for non-owning references
- String builder (GuiarStrBuilder) for efficient string construction
- Comprehensive error handling with error codes and messages
- Advanced search functions (find, rfind, find_any, find_not_any)
- Unicode/UTF-8 support with validation and manipulation functions
- Number conversion functions (to/from int, long, float, double)
- File operations (read/write files to/from strings)
- Formatted string functions (printf-style)
- Split functions with string delimiters and any character delimiters
- Split lines function to handle different line endings
- Replace with limit and replace character functions
- Remove characters function
- String view join function
- CMake build system support
- Shared library support

### Changed
- Improved memory management with exponential growth strategy
- Enhanced performance of all string operations
- Better error checking and handling
- More comprehensive test suite
- Updated documentation

### Fixed
- Memory leaks in error paths
- Buffer overflow potential in some functions
- Unicode handling in reverse function
- Edge cases in split and join functions


---

## [1.2.0] - 2025-08-03

### ✨ Added
- `guiarstr_reverse()` – Safely reverses UTF-8 strings (supports multi-byte characters).
- `guiarstr_contains()` – Checks if a string contains a substring.
- `guiarstr_count()` – Counts non-overlapping occurrences of a substring.
- UTF-8 support in `guiarstr_reverse()`.
- Aliases added for clarity:
  - `guiarstr_starts_with`, `guiarstr_ends_with`
  - `guiarstr_starts_with_ignore_case`, `guiarstr_ends_with_ignore_case`

### 🧪 Testing
- Enhanced output style with colors, sections, and Unicode symbols (✔ ✘).
- Categorized tests by feature (e.g., Trim, Split, Reverse, etc.).
- Improved readability and maintainability of `tests/main.c`.

### 🧹 Changed
- Removed duplicate function definitions in `src/guiarstr.c`.
- Internal code cleanup for consistency and clarity.
- Marked unused internal helper as `static`.

---

## [1.1.0] - 2025-07-27

### ✨ Added
- `guiarstr_starts_with()` – Check if a string starts with a prefix.
- `guiarstr_ends_with()` – Check if a string ends with a suffix.
- `guiarstr_starts_with_ignore_case()` – Case-insensitive version.
- `guiarstr_ends_with_ignore_case()` – Case-insensitive version.
- `examples/usage.c` – A new demo showing usage of all core functions.
- `guiarstr.pc` – `pkg-config` support for easier integration.
- `make install` rule – Installs header, library, and `.pc` file to the system.
- Added support for `$PREFIX` during installation (e.g. `$HOME/.local`).

### 🧪 Testing
- Added new test cases for `starts_with` and `ends_with` functions.
- Clean output showing `[PASS]` per test.

### 🧹 Changed
- Refactored folder layout:
  - Moved tests to `tests/`
  - Moved examples to `examples/`
- Improved function declarations and internal consistency.

---

## [1.0.0] - 2025-07-24

### 🎉 Initial Release
- Core string functions:
  - `guiarstr_trim()`
  - `guiarstr_split()` and `guiarstr_split_free()`
  - `guiarstr_replace()`
  - `guiarstr_toupper()` / `guiarstr_tolower()`
- Basic test suite in `main.c`
- Makefile with `make`, `make test`
- Lightweight and dependency-free
