/*/*
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


#include "guiarstr.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

// Constants
#define GUIARSTR_MIN_CAPACITY 16
#define GUIARSTR_GROWTH_FACTOR 1.5

// Error messages
static const char* error_messages[] = {
    "No error",                           // GUIARSTR_OK
    "Out of memory",                      // GUIARSTR_ERR_MEMORY
    "Null pointer argument",               // GUIARSTR_ERR_NULL
    "Invalid argument",                   // GUIARSTR_ERR_INVALID
    "Buffer overflow",                    // GUIARSTR_ERR_OVERFLOW
    "Invalid UTF-8 sequence",             // GUIARSTR_ERR_UTF8
    "Substring not found"                  // GUIARSTR_ERR_NOT_FOUND
};

// Helper functions
static GuiarStrError guiarstr_ensure_capacity(GuiarStr* str, size_t required) {
    if (str->capacity >= required) {
        return GUIARSTR_OK;
    }
    
    size_t new_capacity = str->capacity;
    while (new_capacity < required) {
        new_capacity = (size_t)(new_capacity * GUIARSTR_GROWTH_FACTOR);
        if (new_capacity < str->capacity) { // Overflow check
            return GUIARSTR_ERR_OVERFLOW;
        }
    }
    
    char* new_data = realloc(str->data, new_capacity);
    if (!new_data) {
        return GUIARSTR_ERR_MEMORY;
    }
    
    str->data = new_data;
    str->capacity = new_capacity;
    return GUIARSTR_OK;
}

// Memory management
GuiarStr* guiarstr_create(const char* str) {
    if (!str) {
        return NULL;
    }
    
    size_t len = strlen(str);
    GuiarStr* result = malloc(sizeof(GuiarStr));
    if (!result) {
        return NULL;
    }
    
    size_t capacity = len + 1;
    if (capacity < GUIARSTR_MIN_CAPACITY) {
        capacity = GUIARSTR_MIN_CAPACITY;
    }
    
    result->data = malloc(capacity);
    if (!result->data) {
        free(result);
        return NULL;
    }
    
    memcpy(result->data, str, len + 1);
    result->length = len;
    result->capacity = capacity;
    
    return result;
}

GuiarStr* guiarstr_create_len(const char* str, size_t len) {
    if (!str) {
        return NULL;
    }
    
    GuiarStr* result = malloc(sizeof(GuiarStr));
    if (!result) {
        return NULL;
    }
    
    size_t capacity = len + 1;
    if (capacity < GUIARSTR_MIN_CAPACITY) {
        capacity = GUIARSTR_MIN_CAPACITY;
    }
    
    result->data = malloc(capacity);
    if (!result->data) {
        free(result);
        return NULL;
    }
    
    memcpy(result->data, str, len);
    result->data[len] = '\0';
    result->length = len;
    result->capacity = capacity;
    
    return result;
}

GuiarStr* guiarstr_create_empty(size_t initial_capacity) {
    GuiarStr* result = malloc(sizeof(GuiarStr));
    if (!result) {
        return NULL;
    }
    
    if (initial_capacity < GUIARSTR_MIN_CAPACITY) {
        initial_capacity = GUIARSTR_MIN_CAPACITY;
    }
    
    result->data = malloc(initial_capacity);
    if (!result->data) {
        free(result);
        return NULL;
    }
    
    result->data[0] = '\0';
    result->length = 0;
    result->capacity = initial_capacity;
    
    return result;
}

GuiarStr* guiarstr_copy(const GuiarStr* str) {
    if (!str) {
        return NULL;
    }
    
    GuiarStr* result = malloc(sizeof(GuiarStr));
    if (!result) {
        return NULL;
    }
    
    result->data = malloc(str->capacity);
    if (!result->data) {
        free(result);
        return NULL;
    }
    
    memcpy(result->data, str->data, str->length + 1);
    result->length = str->length;
    result->capacity = str->capacity;
    
    return result;
}

GuiarStr* guiarstr_view_copy(const GuiarStrView* view) {
    if (!view || !view->data) {
        return NULL;
    }
    
    return guiarstr_create_len(view->data, view->length);
}

void guiarstr_free(GuiarStr* str) {
    if (str) {
        free(str->data);
        free(str);
    }
}

GuiarStrError guiarstr_reserve(GuiarStr* str, size_t new_capacity) {
    GUIARSTR_CHECK_NULL(str);
    
    if (new_capacity <= str->capacity) {
        return GUIARSTR_OK;
    }
    
    char* new_data = realloc(str->data, new_capacity);
    if (!new_data) {
        return GUIARSTR_ERR_MEMORY;
    }
    
    str->data = new_data;
    str->capacity = new_capacity;
    return GUIARSTR_OK;
}

GuiarStrError guiarstr_resize(GuiarStr* str, size_t new_length, char fill_char) {
    GUIARSTR_CHECK_NULL(str);
    
    GuiarStrError err = guiarstr_ensure_capacity(str, new_length + 1);
    if (err != GUIARSTR_OK) {
        return err;
    }
    
    if (new_length > str->length) {
        memset(str->data + str->length, fill_char, new_length - str->length);
    }
    
    str->data[new_length] = '\0';
    str->length = new_length;
    return GUIARSTR_OK;
}

GuiarStrError guiarstr_shrink_to_fit(GuiarStr* str) {
    GUIARSTR_CHECK_NULL(str);
    
    size_t min_capacity = str->length + 1;
    if (min_capacity < GUIARSTR_MIN_CAPACITY) {
        min_capacity = GUIARSTR_MIN_CAPACITY;
    }
    
    if (str->capacity <= min_capacity) {
        return GUIARSTR_OK;
    }
    
    char* new_data = realloc(str->data, min_capacity);
    if (!new_data) {
        return GUIARSTR_ERR_MEMORY;
    }
    
    str->data = new_data;
    str->capacity = min_capacity;
    return GUIARSTR_OK;
}

// Basic string manipulation
char* guiarstr_trim(char* str) {
    if (!str) return NULL;
    
    while (isspace((unsigned char)*str)) str++;
    
    if (*str == '\0') return str;
    
    char* end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    
    *(end + 1) = '\0';
    return str;
}

char* guiarstr_strip(char* str, const char* chars_to_remove) {
    if (!str || !chars_to_remove) return str;
    
    while (*str && strchr(chars_to_remove, *str)) str++;
    
    if (*str == '\0') return str;
    
    char* end = str + strlen(str) - 1;
    while (end > str && strchr(chars_to_remove, *end)) end--;
    
    *(end + 1) = '\0';
    return str;
}

void guiarstr_tolower(char* str) {
    if (!str) return;
    
    for (; *str; ++str) {
        *str = tolower((unsigned char)*str);
    }
}

void guiarstr_toupper(char* str) {
    if (!str) return;
    
    for (; *str; ++str) {
        *str = toupper((unsigned char)*str);
    }
}

// Dynamic string operations
GuiarStrError guiarstr_append(GuiarStr* str, const char* append) {
    if (!append) {
        return GUIARSTR_ERR_NULL;
    }
    
    return guiarstr_append_len(str, append, strlen(append));
}

GuiarStrError guiarstr_append_len(GuiarStr* str, const char* append, size_t len) {
    GUIARSTR_CHECK_NULL(str);
    if (!append && len > 0) {
        return GUIARSTR_ERR_NULL;
    }
    
    if (len == 0) {
        return GUIARSTR_OK;
    }
    
    GuiarStrError err = guiarstr_ensure_capacity(str, str->length + len + 1);
    if (err != GUIARSTR_OK) {
        return err;
    }
    
    memcpy(str->data + str->length, append, len);
    str->length += len;
    str->data[str->length] = '\0';
    
    return GUIARSTR_OK;
}

GuiarStrError guiarstr_append_char(GuiarStr* str, char c) {
    GUIARSTR_CHECK_NULL(str);
    
    GuiarStrError err = guiarstr_ensure_capacity(str, str->length + 2);
    if (err != GUIARSTR_OK) {
        return err;
    }
    
    str->data[str->length++] = c;
    str->data[str->length] = '\0';
    
    return GUIARSTR_OK;
}

GuiarStrError guiarstr_append_view(GuiarStr* str, const GuiarStrView* view) {
    GUIARSTR_CHECK_NULL(str);
    GUIARSTR_CHECK_NULL(view);
    
    return guiarstr_append_len(str, view->data, view->length);
}

GuiarStrError guiarstr_insert(GuiarStr* str, size_t pos, const char* insert) {
    if (!insert) {
        return GUIARSTR_ERR_NULL;
    }
    
    return guiarstr_insert_len(str, pos, insert, strlen(insert));
}

GuiarStrError guiarstr_insert_len(GuiarStr* str, size_t pos, const char* insert, size_t len) {
    GUIARSTR_CHECK_NULL(str);
    if (!insert && len > 0) {
        return GUIARSTR_ERR_NULL;
    }
    
    if (len == 0) {
        return GUIARSTR_OK;
    }
    
    if (pos > str->length) {
        pos = str->length;
    }
    
    GuiarStrError err = guiarstr_ensure_capacity(str, str->length + len + 1);
    if (err != GUIARSTR_OK) {
        return err;
    }
    
    memmove(str->data + pos + len, str->data + pos, str->length - pos);
    memcpy(str->data + pos, insert, len);
    str->length += len;
    str->data[str->length] = '\0';
    
    return GUIARSTR_OK;
}

GuiarStrError guiarstr_insert_char(GuiarStr* str, size_t pos, char c) {
    GUIARSTR_CHECK_NULL(str);
    
    if (pos > str->length) {
        pos = str->length;
    }
    
    GuiarStrError err = guiarstr_ensure_capacity(str, str->length + 2);
    if (err != GUIARSTR_OK) {
        return err;
    }
    
    memmove(str->data + pos + 1, str->data + pos, str->length - pos);
    str->data[pos] = c;
    str->length++;
    str->data[str->length] = '\0';
    
    return GUIARSTR_OK;
}

GuiarStrError guiarstr_remove(GuiarStr* str, size_t pos, size_t len) {
    GUIARSTR_CHECK_NULL(str);
    
    if (pos >= str->length) {
        return GUIARSTR_OK;
    }
    
    if (pos + len > str->length) {
        len = str->length - pos;
    }
    
    memmove(str->data + pos, str->data + pos + len, str->length - pos - len);
    str->length -= len;
    str->data[str->length] = '\0';
    
    return GUIARSTR_OK;
}

GuiarStrError guiarstr_clear(GuiarStr* str) {
    GUIARSTR_CHECK_NULL(str);
    
    str->length = 0;
    str->data[0] = '\0';
    
    return GUIARSTR_OK;
}

// String inspection and search
bool guiarstr_startswith(const char* str, const char* prefix) {
    if (!str || !prefix) return false;
    
    while (*prefix) {
        if (*str++ != *prefix++) return false;
    }
    
    return true;
}

bool guiarstr_endswith(const char* str, const char* suffix) {
    if (!str || !suffix) return false;
    
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    
    if (lensuffix > lenstr) return false;
    
    return strcmp(str + lenstr - lensuffix, suffix) == 0;
}

bool guiarstr_startswithi(const char* str, const char* prefix) {
    if (!str || !prefix) return false;
    
    while (*prefix) {
        if (tolower((unsigned char)*str++) != tolower((unsigned char)*prefix++))
            return false;
    }
    
    return true;
}

bool guiarstr_endswithi(const char* str, const char* suffix) {
    if (!str || !suffix) return false;
    
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    
    if (lensuffix > lenstr) return false;
    
    const char* str_end = str + lenstr - lensuffix;
    while (*suffix) {
        if (tolower((unsigned char)*str_end++) != tolower((unsigned char)*suffix++))
            return false;
    }
    
    return true;
}

bool guiarstr_contains(const char* str, const char* substr) {
    if (!str || !substr) return false;
    
    return strstr(str, substr) != NULL;
}

size_t guiarstr_count(const char* str, const char* substr) {
    if (!str || !substr || !*substr) return 0;
    
    size_t count = 0;
    size_t len = strlen(substr);
    const char* p = str;
    
    while ((p = strstr(p, substr))) {
        count++;
        p += len;
    }
    
    return count;
}

// Advanced search
size_t guiarstr_find(const char* str, const char* substr) {
    if (!str || !substr) return (size_t)-1;
    
    const char* found = strstr(str, substr);
    return found ? (size_t)(found - str) : (size_t)-1;
}

size_t guiarstr_find_from(const char* str, const char* substr, size_t from_pos) {
    if (!str || !substr) return (size_t)-1;
    
    size_t str_len = strlen(str);
    if (from_pos > str_len) return (size_t)-1;
    
    const char* found = strstr(str + from_pos, substr);
    return found ? (size_t)(found - str) : (size_t)-1;
}

size_t guiarstr_rfind(const char* str, const char* substr) {
    if (!str || !substr) return (size_t)-1;
    
    size_t substr_len = strlen(substr);
    if (substr_len == 0) return strlen(str);
    
    size_t str_len = strlen(str);
    if (substr_len > str_len) return (size_t)-1;
    
    for (size_t i = str_len - substr_len; i != (size_t)-1; i--) {
        if (strncmp(str + i, substr, substr_len) == 0) {
            return i;
        }
    }
    
    return (size_t)-1;
}

size_t guiarstr_find_char(const char* str, char c) {
    if (!str) return (size_t)-1;
    
    const char* found = strchr(str, c);
    return found ? (size_t)(found - str) : (size_t)-1;
}

size_t guiarstr_find_char_from(const char* str, char c, size_t from_pos) {
    if (!str) return (size_t)-1;
    
    size_t str_len = strlen(str);
    if (from_pos > str_len) return (size_t)-1;
    
    const char* found = strchr(str + from_pos, c);
    return found ? (size_t)(found - str) : (size_t)-1;
}

size_t guiarstr_rfind_char(const char* str, char c) {
    if (!str) return (size_t)-1;
    
    const char* found = strrchr(str, c);
    return found ? (size_t)(found - str) : (size_t)-1;
}

size_t guiarstr_find_any(const char* str, const char* chars) {
    if (!str || !chars) return (size_t)-1;
    
    return strcspn(str, chars);
}

size_t guiarstr_find_any_from(const char* str, const char* chars, size_t from_pos) {
    if (!str || !chars) return (size_t)-1;
    
    size_t str_len = strlen(str);
    if (from_pos > str_len) return (size_t)-1;
    
    size_t pos = strcspn(str + from_pos, chars);
    return (pos == strlen(str + from_pos)) ? (size_t)-1 : from_pos + pos;
}

size_t guiarstr_find_not_any(const char* str, const char* chars) {
    if (!str || !chars) return (size_t)-1;
    
    return strspn(str, chars);
}

size_t guiarstr_find_not_any_from(const char* str, const char* chars, size_t from_pos) {
    if (!str || !chars) return (size_t)-1;
    
    size_t str_len = strlen(str);
    if (from_pos > str_len) return (size_t)-1;
    
    size_t pos = strspn(str + from_pos, chars);
    return (pos == strlen(str + from_pos)) ? (size_t)-1 : from_pos + pos;
}

// String modification
char* guiarstr_reverse(const char* str) {
    if (!str) return NULL;
    
    size_t len = strlen(str);
    char* reversed = malloc(len + 1);
    if (!reversed) return NULL;
    
    const char* p = str + len;
    char* out = reversed;
    
    while (p > str) {
        const char* start = p - 1;
        while (start > str && (*start & 0xC0) == 0x80) start--;
        
        int char_len = p - start;
        memcpy(out, start, char_len);
        out += char_len;
        p = start;
    }
    
    *out = '\0';
    return reversed;
}

char* guiarstr_replace(const char* str, const char* from, const char* to) {
    return guiarstr_replace_n(str, from, to, (size_t)-1);
}

char* guiarstr_replace_n(const char* str, const char* from, const char* to, size_t max_replacements) {
    if (!str || !from || !to || !*from) return NULL;
    
    size_t from_len = strlen(from);
    size_t to_len = strlen(to);
    size_t count = 0;
    size_t str_len = strlen(str);
    
    // Count occurrences
    const char* tmp = str;
    while ((tmp = strstr(tmp, from)) && (max_replacements == (size_t)-1 || count < max_replacements)) {
        count++;
        tmp += from_len;
    }
    
    size_t result_len = str_len + count * (to_len - from_len);
    char* result = malloc(result_len + 1);
    if (!result) return NULL;
    
    const char* current = str;
    char* dest = result;
    size_t replacements = 0;
    
    while ((tmp = strstr(current, from)) && (max_replacements == (size_t)-1 || replacements < max_replacements)) {
        size_t len = tmp - current;
        memcpy(dest, current, len);
        dest += len;
        memcpy(dest, to, to_len);
        dest += to_len;
        current = tmp + from_len;
        replacements++;
    }
    
    strcpy(dest, current);
    return result;
}

char* guiarstr_replace_char(const char* str, char from, char to) {
    if (!str) return NULL;
    
    size_t len = strlen(str);
    char* result = malloc(len + 1);
    if (!result) return NULL;
    
    for (size_t i = 0; i < len; i++) {
        result[i] = (str[i] == from) ? to : str[i];
    }
    
    result[len] = '\0';
    return result;
}

char* guiarstr_remove_chars(const char* str, const char* chars_to_remove) {
    if (!str || !chars_to_remove) return NULL;
    
    size_t len = strlen(str);
    char* result = malloc(len + 1);
    if (!result) return NULL;
    
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (!strchr(chars_to_remove, str[i])) {
            result[j++] = str[i];
        }
    }
    
    result[j] = '\0';
    return result;
}

// Split and join
char** guiarstr_split(const char* str, char delimiter, size_t* count) {
    if (!str || !count) return NULL;
    
    size_t capacity = 8;
    size_t size = 0;
    char** result = malloc(capacity * sizeof(char*));
    if (!result) return NULL;
    
    const char* start = str;
    const char* ptr = str;
    
    while (*ptr) {
        if (*ptr == delimiter) {
            size_t len = ptr - start;
            char* token = malloc(len + 1);
            if (!token) goto cleanup;
            
            memcpy(token, start, len);
            token[len] = '\0';
            
            if (size >= capacity) {
                capacity *= 2;
                char** temp = realloc(result, capacity * sizeof(char*));
                if (!temp) goto cleanup;
                result = temp;
            }
            
            result[size++] = token;
            start = ptr + 1;
        }
        ptr++;
    }
    
    size_t len = ptr - start;
    char* token = malloc(len + 1);
    if (!token) goto cleanup;
    
    memcpy(token, start, len);
    token[len] = '\0';
    result[size++] = token;
    
    *count = size;
    return result;
    
cleanup:
    for (size_t i = 0; i < size; ++i) free(result[i]);
    free(result);
    *count = 0;
    return NULL;
}

char** guiarstr_split_str(const char* str, const char* delimiter, size_t* count) {
    if (!str || !delimiter || !count) return NULL;
    
    size_t delim_len = strlen(delimiter);
    if (delim_len == 0) {
        // Empty delimiter, return each character as a token
        size_t len = strlen(str);
        char** result = malloc(len * sizeof(char*));
        if (!result) return NULL;
        
        for (size_t i = 0; i < len; i++) {
            result[i] = malloc(2);
            if (!result[i]) {
                for (size_t j = 0; j < i; j++) free(result[j]);
                free(result);
                *count = 0;
                return NULL;
            }
            result[i][0] = str[i];
            result[i][1] = '\0';
        }
        
        *count = len;
        return result;
    }
    
    size_t capacity = 8;
    size_t size = 0;
    char** result = malloc(capacity * sizeof(char*));
    if (!result) return NULL;
    
    const char* start = str;
    const char* ptr = str;
    
    while (*ptr) {
        if (strncmp(ptr, delimiter, delim_len) == 0) {
            size_t len = ptr - start;
            char* token = malloc(len + 1);
            if (!token) goto cleanup;
            
            memcpy(token, start, len);
            token[len] = '\0';
            
            if (size >= capacity) {
                capacity *= 2;
                char** temp = realloc(result, capacity * sizeof(char*));
                if (!temp) goto cleanup;
                result = temp;
            }
            
            result[size++] = token;
            start = ptr + delim_len;
            ptr += delim_len - 1; // Will be incremented in the loop
        }
        ptr++;
    }
    
    size_t len = ptr - start;
    char* token = malloc(len + 1);
    if (!token) goto cleanup;
    
    memcpy(token, start, len);
    token[len] = '\0';
    result[size++] = token;
    
    *count = size;
    return result;
    
cleanup:
    for (size_t i = 0; i < size; ++i) free(result[i]);
    free(result);
    *count = 0;
    return NULL;
}

char** guiarstr_split_any(const char* str, const char* delimiters, size_t* count) {
    if (!str || !delimiters || !count) return NULL;
    
    size_t capacity = 8;
    size_t size = 0;
    char** result = malloc(capacity * sizeof(char*));
    if (!result) return NULL;
    
    const char* start = str;
    const char* ptr = str;
    
    while (*ptr) {
        if (strchr(delimiters, *ptr)) {
            size_t len = ptr - start;
            char* token = malloc(len + 1);
            if (!token) goto cleanup;
            
            memcpy(token, start, len);
            token[len] = '\0';
            
            if (size >= capacity) {
                capacity *= 2;
                char** temp = realloc(result, capacity * sizeof(char*));
                if (!temp) goto cleanup;
                result = temp;
            }
            
            result[size++] = token;
            start = ptr + 1;
        }
        ptr++;
    }
    
    size_t len = ptr - start;
    char* token = malloc(len + 1);
    if (!token) goto cleanup;
    
    memcpy(token, start, len);
    token[len] = '\0';
    result[size++] = token;
    
    *count = size;
    return result;
    
cleanup:
    for (size_t i = 0; i < size; ++i) free(result[i]);
    free(result);
    *count = 0;
    return NULL;
}

char** guiarstr_split_lines(const char* str, size_t* count) {
    if (!str || !count) return NULL;
    
    size_t capacity = 8;
    size_t size = 0;
    char** result = malloc(capacity * sizeof(char*));
    if (!result) return NULL;
    
    const char* start = str;
    const char* ptr = str;
    
    while (*ptr) {
        if (*ptr == '\n' || *ptr == '\r') {
            size_t len = ptr - start;
            char* token = malloc(len + 1);
            if (!token) goto cleanup;
            
            memcpy(token, start, len);
            token[len] = '\0';
            
            if (size >= capacity) {
                capacity *= 2;
                char** temp = realloc(result, capacity * sizeof(char*));
                if (!temp) goto cleanup;
                result = temp;
            }
            
            result[size++] = token;
            
            // Handle CRLF
            if (*ptr == '\r' && *(ptr + 1) == '\n') {
                ptr++;
            }
            
            start = ptr + 1;
        }
        ptr++;
    }
    
    size_t len = ptr - start;
    char* token = malloc(len + 1);
    if (!token) goto cleanup;
    
    memcpy(token, start, len);
    token[len] = '\0';
    result[size++] = token;
    
    *count = size;
    return result;
    
cleanup:
    for (size_t i = 0; i < size; ++i) free(result[i]);
    free(result);
    *count = 0;
    return NULL;
}

void guiarstr_split_free(char** tokens, size_t count) {
    if (!tokens) return;
    
    for (size_t i = 0; i < count; ++i) free(tokens[i]);
    free(tokens);
}

char* guiarstr_join(char** strings, size_t count, const char* separator) {
    if (!strings || !separator) return NULL;
    
    size_t sep_len = strlen(separator);
    size_t total_length = 0;
    
    for (size_t i = 0; i < count; ++i) {
        if (strings[i]) {
            total_length += strlen(strings[i]);
            if (i < count - 1) total_length += sep_len;
        }
    }
    
    char* result = malloc(total_length + 1);
    if (!result) return NULL;
    
    result[0] = '\0';
    
    for (size_t i = 0; i < count; ++i) {
        if (strings[i]) {
            strcat(result, strings[i]);
            if (i < count - 1) strcat(result, separator);
        }
    }
    
    return result;
}

char* guiarstr_join_views(GuiarStrView* views, size_t count, const char* separator) {
    if (!views || !separator) return NULL;
    
    size_t sep_len = strlen(separator);
    size_t total_length = 0;
    
    for (size_t i = 0; i < count; ++i) {
        total_length += views[i].length;
        if (i < count - 1) total_length += sep_len;
    }
    
    char* result = malloc(total_length + 1);
    if (!result) return NULL;
    
    char* ptr = result;
    
    for (size_t i = 0; i < count; ++i) {
        memcpy(ptr, views[i].data, views[i].length);
        ptr += views[i].length;
        
        if (i < count - 1) {
            memcpy(ptr, separator, sep_len);
            ptr += sep_len;
        }
    }
    
    *ptr = '\0';
    return result;
}

// String builder
GuiarStrBuilder* guiarstr_builder_create(size_t initial_capacity) {
    GuiarStrBuilder* builder = malloc(sizeof(GuiarStrBuilder));
    if (!builder) return NULL;
    
    builder->buffer = guiarstr_create_empty(initial_capacity);
    if (!builder->buffer) {
        free(builder);
        return NULL;
    }
    
    builder->parts_count = 0;
    builder->parts_capacity = 16;
    builder->parts = malloc(builder->parts_capacity * sizeof(GuiarStrView));
    if (!builder->parts) {
        guiarstr_free(builder->buffer);
        free(builder);
        return NULL;
    }
    
    return builder;
}

void guiarstr_builder_free(GuiarStrBuilder* builder) {
    if (!builder) return;
    
    guiarstr_free(builder->buffer);
    free(builder->parts);
    free(builder);
}

GuiarStrError guiarstr_builder_append(GuiarStrBuilder* builder, const char* str) {
    GUIARSTR_CHECK_NULL(builder);
    GUIARSTR_CHECK_NULL(str);
    
    GuiarStrView view;
    view.data = str;
    view.length = strlen(str);
    
    return guiarstr_builder_append_view(builder, &view);
}

GuiarStrError guiarstr_builder_append_view(GuiarStrBuilder* builder, const GuiarStrView* view) {
    GUIARSTR_CHECK_NULL(builder);
    GUIARSTR_CHECK_NULL(view);
    
    // Add to parts array
    if (builder->parts_count >= builder->parts_capacity) {
        size_t new_capacity = builder->parts_capacity * 2;
        GuiarStrView* new_parts = realloc(builder->parts, new_capacity * sizeof(GuiarStrView));
        if (!new_parts) return GUIARSTR_ERR_MEMORY;
        
        builder->parts = new_parts;
        builder->parts_capacity = new_capacity;
    }
    
    builder->parts[builder->parts_count++] = *view;
    
    // Also append to buffer
    return guiarstr_append_len(builder->buffer, view->data, view->length);
}

GuiarStrError guiarstr_builder_append_char(GuiarStrBuilder* builder, char c) {
    GUIARSTR_CHECK_NULL(builder);
    
    char str[2] = {c, '\0'};
    return guiarstr_builder_append(builder, str);
}

GuiarStrError guiarstr_builder_append_fmt(GuiarStrBuilder* builder, const char* fmt, ...) {
    GUIARSTR_CHECK_NULL(builder);
    GUIARSTR_CHECK_NULL(fmt);
    
    va_list args;
    va_start(args, fmt);
    GuiarStrError err = guiarstr_builder_append_fmt_va(builder, fmt, args);
    va_end(args);
    
    return err;
}

GuiarStrError guiarstr_builder_append_fmt_va(GuiarStrBuilder* builder, const char* fmt, va_list args) {
    GUIARSTR_CHECK_NULL(builder);
    GUIARSTR_CHECK_NULL(fmt);
    
    // First, determine how much space we need
    va_list args_copy;
    va_copy(args_copy, args);
    int needed = vsnprintf(NULL, 0, fmt, args_copy);
    va_end(args_copy);
    
    if (needed < 0) {
        return GUIARSTR_ERR_INVALID;
    }
    
    // Ensure we have enough space
    GuiarStrError err = guiarstr_ensure_capacity(builder->buffer, builder->buffer->length + needed + 1);
    if (err != GUIARSTR_OK) {
        return err;
    }
    
    // Format directly into the buffer
    int written = vsnprintf(builder->buffer->data + builder->buffer->length, 
                           builder->buffer->capacity - builder->buffer->length, 
                           fmt, args);
    
    if (written < 0) {
        return GUIARSTR_ERR_INVALID;
    }
    
    builder->buffer->length += written;
    
    // Add to parts array
    GuiarStrView view;
    view.data = builder->buffer->data + builder->buffer->length - written;
    view.length = written;
    
    if (builder->parts_count >= builder->parts_capacity) {
        size_t new_capacity = builder->parts_capacity * 2;
        GuiarStrView* new_parts = realloc(builder->parts, new_capacity * sizeof(GuiarStrView));
        if (!new_parts) return GUIARSTR_ERR_MEMORY;
        
        builder->parts = new_parts;
        builder->parts_capacity = new_capacity;
    }
    
    builder->parts[builder->parts_count++] = view;
    
    return GUIARSTR_OK;
}

GuiarStr* guiarstr_builder_build(GuiarStrBuilder* builder) {
    if (!builder) return NULL;
    
    return guiarstr_copy(builder->buffer);
}

GuiarStrError guiarstr_builder_reset(GuiarStrBuilder* builder) {
    GUIARSTR_CHECK_NULL(builder);
    
    GuiarStrError err = guiarstr_clear(builder->buffer);
    if (err != GUIARSTR_OK) {
        return err;
    }
    
    builder->parts_count = 0;
    return GUIARSTR_OK;
}

// Formatting
char* guiarstr_printf(const char* fmt, ...) {
    if (!fmt) return NULL;
    
    va_list args;
    va_start(args, fmt);
    
    // First, determine how much space we need
    va_list args_copy;
    va_copy(args_copy, args);
    int needed = vsnprintf(NULL, 0, fmt, args_copy);
    va_end(args_copy);
    
    if (needed < 0) {
        va_end(args);
        return NULL;
    }
    
    // Allocate the buffer
    char* result = malloc(needed + 1);
    if (!result) {
        va_end(args);
        return NULL;
    }
    
    // Format the string
    int written = vsnprintf(result, needed + 1, fmt, args);
    va_end(args);
    
    if (written < 0) {
        free(result);
        return NULL;
    }
    
    return result;
}

char* guiarstr_vprintf(const char* fmt, va_list args) {
    if (!fmt) return NULL;
    
    // First, determine how much space we need
    va_list args_copy;
    va_copy(args_copy, args);
    int needed = vsnprintf(NULL, 0, fmt, args_copy);
    va_end(args_copy);
    
    if (needed < 0) {
        return NULL;
    }
    
    // Allocate the buffer
    char* result = malloc(needed + 1);
    if (!result) {
        return NULL;
    }
    
    // Format the string
    int written = vsnprintf(result, needed + 1, fmt, args);
    
    if (written < 0) {
        free(result);
        return NULL;
    }
    
    return result;
}

GuiarStrError guiarstr_append_printf(GuiarStr* str, const char* fmt, ...) {
    GUIARSTR_CHECK_NULL(str);
    GUIARSTR_CHECK_NULL(fmt);
    
    va_list args;
    va_start(args, fmt);
    GuiarStrError err = guiarstr_append_vprintf(str, fmt, args);
    va_end(args);
    
    return err;
}

GuiarStrError guiarstr_append_vprintf(GuiarStr* str, const char* fmt, va_list args) {
    GUIARSTR_CHECK_NULL(str);
    GUIARSTR_CHECK_NULL(fmt);
    
    // First, determine how much space we need
    va_list args_copy;
    va_copy(args_copy, args);
    int needed = vsnprintf(NULL, 0, fmt, args_copy);
    va_end(args_copy);
    
    if (needed < 0) {
        return GUIARSTR_ERR_INVALID;
    }
    
    // Ensure we have enough space
    GuiarStrError err = guiarstr_ensure_capacity(str, str->length + needed + 1);
    if (err != GUIARSTR_OK) {
        return err;
    }
    
    // Format directly into the buffer
    int written = vsnprintf(str->data + str->length, 
                           str->capacity - str->length, 
                           fmt, args);
    
    if (written < 0) {
        return GUIARSTR_ERR_INVALID;
    }
    
    str->length += written;
    return GUIARSTR_OK;
}

// Unicode/UTF-8 support
size_t guiarstr_utf8_len(const char* str) {
    if (!str) return 0;
    
    size_t len = 0;
    for (; *str; str++) {
        if ((*str & 0xC0) != 0x80) {
            len++;
        }
    }
    
    return len;
}

size_t guiarstr_utf8_char_len(const char* str, size_t byte_pos) {
    if (!str) return 0;
    
    size_t str_len = strlen(str);
    if (byte_pos >= str_len) return 0;
    
    unsigned char c = (unsigned char)str[byte_pos];
    if ((c & 0x80) == 0x00) return 1;      // 0xxxxxxx
    if ((c & 0xE0) == 0xC0) return 2;      // 110xxxxx
    if ((c & 0xF0) == 0xE0) return 3;      // 1110xxxx
    if ((c & 0xF8) == 0xF0) return 4;      // 11110xxx
    
    return 1; // Invalid UTF-8, treat as single byte
}

size_t guiarstr_utf8_byte_pos(const char* str, size_t char_pos) {
    if (!str) return 0;
    
    size_t byte_pos = 0;
    size_t current_char = 0;
    
    while (str[byte_pos]) {
        if (current_char == char_pos) {
            return byte_pos;
        }
        
        if ((str[byte_pos] & 0xC0) != 0x80) {
            current_char++;
        }
        
        byte_pos++;
    }
    
    return byte_pos;
}

GuiarStrError guiarstr_utf8_append(GuiarStr* str, const char* utf8_str) {
    GUIARSTR_CHECK_NULL(str);
    GUIARSTR_CHECK_NULL(utf8_str);
    
    // Validate UTF-8
    if (!guiarstr_utf8_validate(utf8_str)) {
        return GUIARSTR_ERR_UTF8;
    }
    
    return guiarstr_append(str, utf8_str);
}

GuiarStrError guiarstr_utf8_insert(GuiarStr* str, size_t char_pos, const char* utf8_str) {
    GUIARSTR_CHECK_NULL(str);
    GUIARSTR_CHECK_NULL(utf8_str);
    
    // Validate UTF-8
    if (!guiarstr_utf8_validate(utf8_str)) {
        return GUIARSTR_ERR_UTF8;
    }
    
    // Convert character position to byte position
    size_t byte_pos = guiarstr_utf8_byte_pos(str->data, char_pos);
    
    return guiarstr_insert(str, byte_pos, utf8_str);
}

GuiarStrError guiarstr_utf8_remove(GuiarStr* str, size_t char_pos, size_t char_len) {
    GUIARSTR_CHECK_NULL(str);
    
    // Convert character positions to byte positions
    size_t start_byte_pos = guiarstr_utf8_byte_pos(str->data, char_pos);
    size_t end_byte_pos = guiarstr_utf8_byte_pos(str->data, char_pos + char_len);
    
    return guiarstr_remove(str, start_byte_pos, end_byte_pos - start_byte_pos);
}

char* guiarstr_utf8_substring(const char* str, size_t char_pos, size_t char_len) {
    if (!str) return NULL;
    
    // Convert character positions to byte positions
    size_t start_byte_pos = guiarstr_utf8_byte_pos(str, char_pos);
    size_t end_byte_pos = guiarstr_utf8_byte_pos(str, char_pos + char_len);
    
    // Extract the substring
    size_t len = end_byte_pos - start_byte_pos;
    char* result = malloc(len + 1);
    if (!result) return NULL;
    
    memcpy(result, str + start_byte_pos, len);
    result[len] = '\0';
    
    return result;
}

char* guiarstr_utf8_reverse(const char* str) {
    if (!str) return NULL;
    
    // Validate UTF-8
    if (!guiarstr_utf8_validate(str)) {
        return NULL;
    }
    
    size_t len = strlen(str);
    char* reversed = malloc(len + 1);
    if (!reversed) return NULL;
    
    const char* p = str + len;
    char* out = reversed;
    
    while (p > str) {
        const char* start = p - 1;
        while (start > str && (*start & 0xC0) == 0x80) start--;
        
        int char_len = p - start;
        memcpy(out, start, char_len);
        out += char_len;
        p = start;
    }
    
    *out = '\0';
    return reversed;
}

bool guiarstr_utf8_validate(const char* str) {
    if (!str) return false;
    
    for (; *str; ) {
        unsigned char c = (unsigned char)*str;
        
        if ((c & 0x80) == 0x00) {
            // ASCII character
            str++;
        } else if ((c & 0xE0) == 0xC0) {
            // 2-byte sequence
            if ((str[1] & 0xC0) != 0x80) return false;
            str += 2;
        } else if ((c & 0xF0) == 0xE0) {
            // 3-byte sequence
            if ((str[1] & 0xC0) != 0x80 || (str[2] & 0xC0) != 0x80) return false;
            str += 3;
        } else if ((c & 0xF8) == 0xF0) {
            // 4-byte sequence
            if ((str[1] & 0xC0) != 0x80 || (str[2] & 0xC0) != 0x80 || (str[3] & 0xC0) != 0x80) return false;
            str += 4;
        } else {
            // Invalid UTF-8
            return false;
        }
    }
    
    return true;
}

size_t guiarstr_utf8_width(const char* str) {
    if (!str) return 0;
    
    size_t width = 0;
    
    for (; *str; ) {
        unsigned char c = (unsigned char)*str;
        size_t char_len;
        
        if ((c & 0x80) == 0x00) {
            // ASCII character
            char_len = 1;
            width++;
        } else if ((c & 0xE0) == 0xC0) {
            // 2-byte sequence
            char_len = 2;
            width++;
        } else if ((c & 0xF0) == 0xE0) {
            // 3-byte sequence
            char_len = 3;
            width++;
        } else if ((c & 0xF8) == 0xF0) {
            // 4-byte sequence
            char_len = 4;
            width += 2; // Most 4-byte sequences are CJK characters, which are typically displayed as double-width
        } else {
            // Invalid UTF-8, skip
            char_len = 1;
            width++;
        }
        
        str += char_len;
    }
    
    return width;
}

// Conversion
int guiarstr_to_int(const char* str, bool* success) {
    if (!str) {
        if (success) *success = false;
        return 0;
    }
    
    char* endptr;
    errno = 0;
    long val = strtol(str, &endptr, 10);
    
    if (errno == ERANGE || val < INT_MIN || val > INT_MAX || endptr == str) {
        if (success) *success = false;
        return 0;
    }
    
    if (success) *success = true;
    return (int)val;
}

long guiarstr_to_long(const char* str, bool* success) {
    if (!str) {
        if (success) *success = false;
        return 0;
    }
    
    char* endptr;
    errno = 0;
    long val = strtol(str, &endptr, 10);
    
    if (errno == ERANGE || endptr == str) {
        if (success) *success = false;
        return 0;
    }
    
    if (success) *success = true;
    return val;
}

long long guiarstr_to_long_long(const char* str, bool* success) {
    if (!str) {
        if (success) *success = false;
        return 0;
    }
    
    char* endptr;
    errno = 0;
    long long val = strtoll(str, &endptr, 10);
    
    if (errno == ERANGE || endptr == str) {
        if (success) *success = false;
        return 0;
    }
    
    if (success) *success = true;
    return val;
}

unsigned int guiarstr_to_uint(const char* str, bool* success) {
    if (!str) {
        if (success) *success = false;
        return 0;
    }
    
    char* endptr;
    errno = 0;
    unsigned long val = strtoul(str, &endptr, 10);
    
    if (errno == ERANGE || val > UINT_MAX || endptr == str) {
        if (success) *success = false;
        return 0;
    }
    
    if (success) *success = true;
    return (unsigned int)val;
}

unsigned long guiarstr_to_ulong(const char* str, bool* success) {
    if (!str) {
        if (success) *success = false;
        return 0;
    }
    
    char* endptr;
    errno = 0;
    unsigned long val = strtoul(str, &endptr, 10);
    
    if (errno == ERANGE || endptr == str) {
        if (success) *success = false;
        return 0;
    }
    
    if (success) *success = true;
    return val;
}

unsigned long long guiarstr_to_ulong_long(const char* str, bool* success) {
    if (!str) {
        if (success) *success = false;
        return 0;
    }
    
    char* endptr;
    errno = 0;
    unsigned long long val = strtoull(str, &endptr, 10);
    
    if (errno == ERANGE || endptr == str) {
        if (success) *success = false;
        return 0;
    }
    
    if (success) *success = true;
    return val;
}

float guiarstr_to_float(const char* str, bool* success) {
    if (!str) {
        if (success) *success = false;
        return 0.0f;
    }
    
    char* endptr;
    errno = 0;
    float val = strtof(str, &endptr);
    
    if (errno == ERANGE || endptr == str) {
        if (success) *success = false;
        return 0.0f;
    }
    
    if (success) *success = true;
    return val;
}

double guiarstr_to_double(const char* str, bool* success) {
    if (!str) {
        if (success) *success = false;
        return 0.0;
    }
    
    char* endptr;
    errno = 0;
    double val = strtod(str, &endptr);
    
    if (errno == ERANGE || endptr == str) {
        if (success) *success = false;
        return 0.0;
    }
    
    if (success) *success = true;
    return val;
}

char* guiarstr_from_int(int value) {
    char* result = malloc(12); // Enough for 32-bit int
    if (!result) return NULL;
    
    snprintf(result, 12, "%d", value);
    return result;
}

char* guiarstr_from_long(long value) {
    char* result = malloc(24); // Enough for 64-bit long
    if (!result) return NULL;
    
    snprintf(result, 24, "%ld", value);
    return result;
}

char* guiarstr_from_long_long(long long value) {
    char* result = malloc(24); // Enough for 64-bit long long
    if (!result) return NULL;
    
    snprintf(result, 24, "%lld", value);
    return result;
}

char* guiarstr_from_uint(unsigned int value) {
    char* result = malloc(12); // Enough for 32-bit uint
    if (!result) return NULL;
    
    snprintf(result, 12, "%u", value);
    return result;
}

char* guiarstr_from_ulong(unsigned long value) {
    char* result = malloc(24); // Enough for 64-bit ulong
    if (!result) return NULL;
    
    snprintf(result, 24, "%lu", value);
    return result;
}

char* guiarstr_from_ulong_long(unsigned long long value) {
    char* result = malloc(24); // Enough for 64-bit ulong long
    if (!result) return NULL;
    
    snprintf(result, 24, "%llu", value);
    return result;
}

char* guiarstr_from_float(float value, int precision) {
    // Calculate required buffer size
    int int_part = (int)value;
    int int_digits = 1;
    while (int_part /= 10) int_digits++;
    
    int buf_size = int_digits + precision + 3; // sign, decimal point, null terminator
    
    char* result = malloc(buf_size);
    if (!result) return NULL;
    
    snprintf(result, buf_size, "%.*f", precision, value);
    return result;
}

char* guiarstr_from_double(double value, int precision) {
    // Calculate required buffer size
    long long int_part = (long long)value;
    int int_digits = 1;
    while (int_part /= 10) int_digits++;
    
    int buf_size = int_digits + precision + 3; // sign, decimal point, null terminator
    
    char* result = malloc(buf_size);
    if (!result) return NULL;
    
    snprintf(result, buf_size, "%.*f", precision, value);
    return result;
}

// File operations
GuiarStr* guiarstr_read_file(const char* filename, GuiarStrError* error) {
    if (!filename) {
        if (error) *error = GUIARSTR_ERR_NULL;
        return NULL;
    }
    
    FILE* file = fopen(filename, "rb");
    if (!file) {
        if (error) *error = GUIARSTR_ERR_INVALID;
        return NULL;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (file_size < 0) {
        fclose(file);
        if (error) *error = GUIARSTR_ERR_INVALID;
        return NULL;
    }
    
    // Create string with capacity to hold the file
    GuiarStr* result = guiarstr_create_empty(file_size);
    if (!result) {
        fclose(file);
        if (error) *error = GUIARSTR_ERR_MEMORY;
        return NULL;
    }
    
    // Read file content
    size_t bytes_read = fread(result->data, 1, file_size, file);
    fclose(file);
    
    if (bytes_read != (size_t)file_size) {
        guiarstr_free(result);
        if (error) *error = GUIARSTR_ERR_INVALID;
        return NULL;
    }
    
    result->length = file_size;
    result->data[file_size] = '\0';
    
    if (error) *error = GUIARSTR_OK;
    return result;
}

GuiarStrError guiarstr_write_file(const char* filename, const char* str, bool append) {
    if (!filename || !str) {
        return GUIARSTR_ERR_NULL;
    }
    
    FILE* file = fopen(filename, append ? "ab" : "wb");
    if (!file) {
        return GUIARSTR_ERR_INVALID;
    }
    
    size_t len = strlen(str);
    size_t bytes_written = fwrite(str, 1, len, file);
    fclose(file);
    
    if (bytes_written != len) {
        return GUIARSTR_ERR_INVALID;
    }
    
    return GUIARSTR_OK;
}

GuiarStrError guiarstr_write_file_view(const char* filename, const GuiarStrView* view, bool append) {
    if (!filename || !view || !view->data) {
        return GUIARSTR_ERR_NULL;
    }
    
    FILE* file = fopen(filename, append ? "ab" : "wb");
    if (!file) {
        return GUIARSTR_ERR_INVALID;
    }
    
    size_t bytes_written = fwrite(view->data, 1, view->length, file);
    fclose(file);
    
    if (bytes_written != view->length) {
        return GUIARSTR_ERR_INVALID;
    }
    
    return GUIARSTR_OK;
}

// Error handling
const char* guiarstr_error_message(GuiarStrError error) {
    if (error < 0 || error >= sizeof(error_messages) / sizeof(error_messages[0])) {
        return "Unknown error";
    }
    
    return error_messages[error];
}
