# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/).

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
