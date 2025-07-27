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

#ifndef GUIARSTR_H
#define GUIARSTR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>  // for size_t
#include <stdbool.h> // for bool

/**
 * @brief Removes leading and trailing whitespace from a string in place.
 *
 * @param str The string to be trimmed. It must be null-terminated.
 * @return A pointer to the trimmed string (may be moved forward).
 */
char* guiarstr_trim(char* str);

/**
 * @brief Splits a string into tokens using a delimiter.
 *
 * @param str The input string (will not be modified).
 * @param delimiter The delimiter character.
 * @param count Output: Number of tokens returned.
 * @return An array of strings (must be freed using guiarstr_split_free).
 */
char** guiarstr_split(const char* str, char delimiter, size_t* count);

/**
 * @brief Frees the memory returned by guiarstr_split.
 *
 * @param tokens The array of strings.
 * @param count The number of strings.
 */
void guiarstr_split_free(char** tokens, size_t count);

/**
 * @brief Replaces all occurrences of a substring with another string.
 *
 * @param str The input string.
 * @param from The substring to replace.
 * @param to The replacement substring.
 * @return A newly allocated string (caller must free it).
 */
char* guiarstr_replace(const char* str, const char* from, const char* to);

/**
 * @brief Converts a string to lowercase in place.
 *
 * @param str The string to modify.
 */
void guiarstr_tolower(char* str);

/**
 * @brief Converts a string to uppercase in place.
 *
 * @param str The string to modify.
 */
void guiarstr_toupper(char* str);

/**
 * @brief Checks if a string starts with a given prefix.
 *
 * @param str The input string.
 * @param prefix The prefix to check.
 * @return true if str starts with prefix, false otherwise.
 */
bool guiarstr_startswith(const char* str, const char* prefix);

/**
 * @brief Strips specified characters from both ends of a string in place.
 *
 * @param str The string to modify.
 * @param chars_to_remove A string of characters to strip.
 * @return A pointer to the stripped string (may be moved forward).
 */
char* guiarstr_strip(char* str, const char* chars_to_remove);

/**
 * @brief Joins an array of strings with a separator.
 *
 * @param strings Array of strings.
 * @param count Number of strings.
 * @param separator Separator string.
 * @return A newly allocated joined string (caller must free it).
 */
char* guiarstr_join(char** strings, size_t count, const char* separator);

#ifdef __cplusplus
}
#endif

#endif // GUIARSTR_H
