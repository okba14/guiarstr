/*
 * GuiarStr - Advanced C String Utilities Library
 * 
 * Author: GUIAR OQBA
 * Email: techokba@gmail.com
 * Website: https://okba14.github.io
 * Phone: +2136-71-36-04-38
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

/**
 * @brief Determines the number of bytes a UTF-8 character uses based on its first byte.
 */
static int utf8_char_len(unsigned char c) {
    if ((c & 0x80) == 0x00) return 1;
    if ((c & 0xE0) == 0xC0) return 2;
    if ((c & 0xF0) == 0xE0) return 3;
    if ((c & 0xF8) == 0xF0) return 4;
    return 1;
}

// ─────────────────────────────────────────────────────────────
// ─────────────── Basic string manipulation ───────────────────
// ─────────────────────────────────────────────────────────────

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
    for (; *str; ++str) *str = tolower((unsigned char)*str);
}

void guiarstr_toupper(char* str) {
    if (!str) return;
    for (; *str; ++str) *str = toupper((unsigned char)*str);
}

// ─────────────────────────────────────────────────────────────
// ─────────────── String inspection and search ────────────────
// ─────────────────────────────────────────────────────────────

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

// ─────────────────────────────────────────────────────────────
// ─────────────── String allocation/modification ──────────────
// ─────────────────────────────────────────────────────────────

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
    if (!str || !from || !to || !*from) return NULL;
    size_t from_len = strlen(from);
    size_t to_len = strlen(to);
    size_t count = 0;
    const char* tmp = str;

    while ((tmp = strstr(tmp, from))) {
        count++;
        tmp += from_len;
    }

    size_t result_len = strlen(str) + count * (to_len - from_len);
    char* result = malloc(result_len + 1);
    if (!result) return NULL;

    const char* current = str;
    char* dest = result;

    while ((tmp = strstr(current, from))) {
        size_t len = tmp - current;
        memcpy(dest, current, len);
        dest += len;
        memcpy(dest, to, to_len);
        dest += to_len;
        current = tmp + from_len;
    }

    strcpy(dest, current);
    return result;
}

char* guiarstr_join(char** strings, size_t count, const char* separator) {
    if (!strings || !separator) return NULL;
    size_t sep_len = strlen(separator);
    size_t total_length = 0;

    for (size_t i = 0; i < count; ++i) {
        total_length += strlen(strings[i]);
        if (i < count - 1) total_length += sep_len;
    }

    char* result = malloc(total_length + 1);
    if (!result) return NULL;
    result[0] = '\0';

    for (size_t i = 0; i < count; ++i) {
        strcat(result, strings[i]);
        if (i < count - 1) strcat(result, separator);
    }
    return result;
}

// ─────────────────────────────────────────────────────────────
// ─────────────── Split/Free helper functions ─────────────────
// ─────────────────────────────────────────────────────────────

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

void guiarstr_split_free(char** tokens, size_t count) {
    if (!tokens) return;
    for (size_t i = 0; i < count; ++i) free(tokens[i]);
    free(tokens);
}

