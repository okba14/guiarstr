/*
 * GuiarStr - Advanced C String Utilities Library
 * 
 * Author: GUIAR OQBA (c) 2025
 * Email: techokba@gmail.com
 * Website: https://okba14.github.io
 * Repository: https://github.com/okba14/guiarstr
 * 
 * License: MIT License
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 */



#ifndef GUIARSTR_H
#define GUIARSTR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>  // for size_t
#include <stdbool.h> // for bool
#include <stdarg.h>  // for va_list

// Error codes
typedef enum {
    GUIARSTR_OK = 0,
    GUIARSTR_ERR_MEMORY,
    GUIARSTR_ERR_NULL,
    GUIARSTR_ERR_INVALID,
    GUIARSTR_ERR_OVERFLOW,
    GUIARSTR_ERR_UTF8,
    GUIARSTR_ERR_NOT_FOUND
} GuiarStrError;

// Dynamic string structure
typedef struct {
    char* data;
    size_t length;
    size_t capacity;
} GuiarStr;

// String view structure (non-owning reference)

typedef struct {
    const char* data;
    size_t length;
} GuiarStrView;

// String builder structure

typedef struct {
    GuiarStr* buffer;
    size_t parts_count;
    size_t parts_capacity;
    GuiarStrView* parts;
} GuiarStrBuilder;

// Memory management

GuiarStr* guiarstr_create(const char* str);
GuiarStr* guiarstr_create_len(const char* str, size_t len);
GuiarStr* guiarstr_create_empty(size_t initial_capacity);
GuiarStr* guiarstr_copy(const GuiarStr* str);
GuiarStr* guiarstr_view_copy(const GuiarStrView* view);
void guiarstr_free(GuiarStr* str);
GuiarStrError guiarstr_reserve(GuiarStr* str, size_t new_capacity);
GuiarStrError guiarstr_resize(GuiarStr* str, size_t new_length, char fill_char);
GuiarStrError guiarstr_shrink_to_fit(GuiarStr* str);

// Basic operations (existing)

char* guiarstr_trim(char* str);
char* guiarstr_strip(char* str, const char* chars_to_remove);
void guiarstr_tolower(char* str);
void guiarstr_toupper(char* str);

// Dynamic string operations

GuiarStrError guiarstr_append(GuiarStr* str, const char* append);
GuiarStrError guiarstr_append_len(GuiarStr* str, const char* append, size_t len);
GuiarStrError guiarstr_append_char(GuiarStr* str, char c);
GuiarStrError guiarstr_append_view(GuiarStr* str, const GuiarStrView* view);
GuiarStrError guiarstr_insert(GuiarStr* str, size_t pos, const char* insert);
GuiarStrError guiarstr_insert_len(GuiarStr* str, size_t pos, const char* insert, size_t len);
GuiarStrError guiarstr_insert_char(GuiarStr* str, size_t pos, char c);
GuiarStrError guiarstr_remove(GuiarStr* str, size_t pos, size_t len);
GuiarStrError guiarstr_clear(GuiarStr* str);

// String inspection and search (existing with improvements)

bool guiarstr_startswith(const char* str, const char* prefix);
bool guiarstr_endswith(const char* str, const char* suffix);
bool guiarstr_startswithi(const char* str, const char* prefix);
bool guiarstr_endswithi(const char* str, const char* suffix);
bool guiarstr_contains(const char* str, const char* substr);
size_t guiarstr_count(const char* str, const char* substr);

// Advanced search

size_t guiarstr_find(const char* str, const char* substr);
size_t guiarstr_find_from(const char* str, const char* substr, size_t from_pos);
size_t guiarstr_rfind(const char* str, const char* substr);
size_t guiarstr_find_char(const char* str, char c);
size_t guiarstr_find_char_from(const char* str, char c, size_t from_pos);
size_t guiarstr_rfind_char(const char* str, char c);
size_t guiarstr_find_any(const char* str, const char* chars);
size_t guiarstr_find_any_from(const char* str, const char* chars, size_t from_pos);
size_t guiarstr_find_not_any(const char* str, const char* chars);
size_t guiarstr_find_not_any_from(const char* str, const char* chars, size_t from_pos);

// String modification (existing with improvements)

char* guiarstr_reverse(const char* str);
char* guiarstr_replace(const char* str, const char* from, const char* to);
char* guiarstr_replace_n(const char* str, const char* from, const char* to, size_t max_replacements);
char* guiarstr_replace_char(const char* str, char from, char to);
char* guiarstr_remove_chars(const char* str, const char* chars_to_remove);

// Split and join (existing with improvements)

char** guiarstr_split(const char* str, char delimiter, size_t* count);
char** guiarstr_split_str(const char* str, const char* delimiter, size_t* count);
char** guiarstr_split_any(const char* str, const char* delimiters, size_t* count);
char** guiarstr_split_lines(const char* str, size_t* count);
void guiarstr_split_free(char** tokens, size_t count);
char* guiarstr_join(char** strings, size_t count, const char* separator);
char* guiarstr_join_views(GuiarStrView* views, size_t count, const char* separator);

// String builder

GuiarStrBuilder* guiarstr_builder_create(size_t initial_capacity);
void guiarstr_builder_free(GuiarStrBuilder* builder);
GuiarStrError guiarstr_builder_append(GuiarStrBuilder* builder, const char* str);
GuiarStrError guiarstr_builder_append_view(GuiarStrBuilder* builder, const GuiarStrView* view);
GuiarStrError guiarstr_builder_append_char(GuiarStrBuilder* builder, char c);
GuiarStrError guiarstr_builder_append_fmt(GuiarStrBuilder* builder, const char* fmt, ...);
GuiarStrError guiarstr_builder_append_fmt_va(GuiarStrBuilder* builder, const char* fmt, va_list args);
GuiarStr* guiarstr_builder_build(GuiarStrBuilder* builder);
GuiarStrError guiarstr_builder_reset(GuiarStrBuilder* builder);

// Formatting

char* guiarstr_printf(const char* fmt, ...);
char* guiarstr_vprintf(const char* fmt, va_list args);
GuiarStrError guiarstr_append_printf(GuiarStr* str, const char* fmt, ...);
GuiarStrError guiarstr_append_vprintf(GuiarStr* str, const char* fmt, va_list args);

// Unicode/UTF-8 support

size_t guiarstr_utf8_len(const char* str);
size_t guiarstr_utf8_char_len(const char* str, size_t byte_pos);
size_t guiarstr_utf8_byte_pos(const char* str, size_t char_pos);
GuiarStrError guiarstr_utf8_append(GuiarStr* str, const char* utf8_str);
GuiarStrError guiarstr_utf8_insert(GuiarStr* str, size_t char_pos, const char* utf8_str);
GuiarStrError guiarstr_utf8_remove(GuiarStr* str, size_t char_pos, size_t char_len);
char* guiarstr_utf8_substring(const char* str, size_t char_pos, size_t char_len);
char* guiarstr_utf8_reverse(const char* str);
bool guiarstr_utf8_validate(const char* str);
size_t guiarstr_utf8_width(const char* str); // Display width for monospace fonts

// Conversion

int guiarstr_to_int(const char* str, bool* success);
long guiarstr_to_long(const char* str, bool* success);
long long guiarstr_to_long_long(const char* str, bool* success);
unsigned int guiarstr_to_uint(const char* str, bool* success);
unsigned long guiarstr_to_ulong(const char* str, bool* success);
unsigned long long guiarstr_to_ulong_long(const char* str, bool* success);
float guiarstr_to_float(const char* str, bool* success);
double guiarstr_to_double(const char* str, bool* success);
char* guiarstr_from_int(int value);
char* guiarstr_from_long(long value);
char* guiarstr_from_long_long(long long value);
char* guiarstr_from_uint(unsigned int value);
char* guiarstr_from_ulong(unsigned long value);
char* guiarstr_from_ulong_long(unsigned long long value);
char* guiarstr_from_float(float value, int precision);
char* guiarstr_from_double(double value, int precision);

// File operations

GuiarStr* guiarstr_read_file(const char* filename, GuiarStrError* error);
GuiarStrError guiarstr_write_file(const char* filename, const char* str, bool append);
GuiarStrError guiarstr_write_file_view(const char* filename, const GuiarStrView* view, bool append);

// Error handling

const char* guiarstr_error_message(GuiarStrError error);

// Utility macros

#define GUIARSTR_CHECK_NULL(ptr) \
    do { \
        if (!(ptr)) return GUIARSTR_ERR_NULL; \
    } while (0)

#define GUIARSTR_CHECK_NULL_RET_NULL(ptr) \
    do { \
        if (!(ptr)) return NULL; \
    } while (0)

#define GUIARSTR_CHECK_NULL_RET_FALSE(ptr) \
    do { \
        if (!(ptr)) return false; \
    } while (0)

#define GUIARSTR_CHECK_NULL_RET_ZERO(ptr) \
    do { \
        if (!(ptr)) return 0; \
    } while (0)

// Friendly aliases (existing)

#define guiarstr_starts_with     guiarstr_startswith
#define guiarstr_ends_with       guiarstr_endswith
#define guiarstr_starts_withi    guiarstr_startswithi
#define guiarstr_ends_withi      guiarstr_endswithi

#ifdef __cplusplus
}
#endif

#endif // GUIARSTR_H
