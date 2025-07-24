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
#include <ctype.h>    // tolower, toupper, isspace
#include <string.h>   // strlen, strstr, memcpy, strcmp
#include <stdlib.h>   // malloc, free

char* guiarstr_trim(char* str) {
    if (!str) return NULL;

    // Trim leading
    while (isspace((unsigned char)*str)) str++;

    if (*str == '\0') return str;

    // Trim trailing
    char* end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    *(end + 1) = '\0';
    return str;
}

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

    // last token
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
    for (size_t i = 0; i < count; ++i) {
        free(tokens[i]);
    }
    free(tokens);
}

char* guiarstr_replace(const char* str, const char* from, const char* to) {
    if (!str || !from || !to || !*from) return NULL;

    size_t from_len = strlen(from);
    size_t to_len = strlen(to);

    // First, count how many replacements are needed
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

    strcpy(dest, current); // copy remaining
    return result;
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

