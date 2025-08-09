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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../include/guiarstr.h"

// === Colors and symbols ===
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"
#define CHECK   "\xE2\x9C\x94"  // ✔
#define CROSS   "\xE2\x9C\x98"  // ✘

#define SECTION(title) \
    printf("\n" CYAN "==[ %s ]%.*s\n" RESET, title, 58 - (int)strlen(title), "==================================================")

#define ASSERT_EQ_STR(actual, expected) \
    do { \
        if (strcmp(actual, expected) != 0) { \
            fprintf(stderr, RED "[%s] \"%s\" != \"%s\" (line %d)\n" RESET, CROSS, actual, expected, __LINE__); \
            exit(1); \
        } else { \
            printf(GREEN "[%s] %-22s\"%s\"\n" RESET, CHECK, "", actual); \
        } \
    } while (0)

#define ASSERT_EQ_SIZE(actual, expected) \
    do { \
        if ((actual) != (expected)) { \
            fprintf(stderr, RED "[%s] %zu != %zu (line %d)\n" RESET, CROSS, (size_t)(actual), (size_t)(expected), __LINE__); \
            exit(1); \
        } else { \
            printf(GREEN "[%s] %-22s%zu == %zu (line %d)\n" RESET, CHECK, "", (size_t)(actual), (size_t)(expected), __LINE__); \
        } \
    } while (0)

#define ASSERT_TRUE(expr) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, RED "[%s] ASSERT_TRUE failed (line %d)\n" RESET, CROSS, __LINE__); \
            exit(1); \
        } else { \
            printf(GREEN "[%s] ASSERT_TRUE\n" RESET, CHECK); \
        } \
    } while (0)

#define ASSERT_FALSE(expr) \
    do { \
        if (expr) { \
            fprintf(stderr, RED "[%s] ASSERT_FALSE failed (line %d)\n" RESET, CROSS, __LINE__); \
            exit(1); \
        } else { \
            printf(GREEN "[%s] ASSERT_FALSE\n" RESET, CHECK); \
        } \
    } while (0)

#define ASSERT_EQ_ERR(actual, expected) \
    do { \
        if ((actual) != (expected)) { \
            fprintf(stderr, RED "[%s] Error %d != %d (line %d)\n" RESET, CROSS, (int)(actual), (int)(expected), __LINE__); \
            exit(1); \
        } else { \
            printf(GREEN "[%s] Error code: %d (%s)\n" RESET, CHECK, (int)(actual), guiarstr_error_message(actual)); \
        } \
    } while (0)

int main(void) {
    printf("\n==================== GuiarStr Test Suite ====================\n");
    
    SECTION("Trim Tests");
    char trim1[] = "  hello world  ";
    ASSERT_EQ_STR(guiarstr_trim(trim1), "hello world");
    
    char trim2[] = "   ";
    ASSERT_EQ_STR(guiarstr_trim(trim2), "");
    
    SECTION("Strip Tests");
    char strip1[] = "***hello***";
    ASSERT_EQ_STR(guiarstr_strip(strip1, "*"), "hello");
    
    char strip2[] = "!!abc!!";
    ASSERT_EQ_STR(guiarstr_strip(strip2, "!"), "abc");
    
    char strip3[] = "><><okba><>";
    ASSERT_EQ_STR(guiarstr_strip(strip3, "><"), "okba");
    
    SECTION("ToLower / ToUpper");
    char lower[] = "HeLLo GUIAR";
    guiarstr_tolower(lower);
    ASSERT_EQ_STR(lower, "hello guiar");
    
    char upper[] = "guiarStr";
    guiarstr_toupper(upper);
    ASSERT_EQ_STR(upper, "GUIARSTR");
    
    SECTION("Split Tests");
    size_t count;
    char** parts = guiarstr_split("one,two,three", ',', &count);
    ASSERT_EQ_SIZE(count, 3);
    ASSERT_EQ_STR(parts[0], "one");
    ASSERT_EQ_STR(parts[1], "two");
    ASSERT_EQ_STR(parts[2], "three");
    guiarstr_split_free(parts, count);
    
    // Split with string delimiter
    char** parts2 = guiarstr_split_str("oneXYZtwoXYZthree", "XYZ", &count);
    ASSERT_EQ_SIZE(count, 3);
    ASSERT_EQ_STR(parts2[0], "one");
    ASSERT_EQ_STR(parts2[1], "two");
    ASSERT_EQ_STR(parts2[2], "three");
    guiarstr_split_free(parts2, count);
    
    // Split with any delimiter
    char** parts3 = guiarstr_split_any("one,two;three|four", ",;|", &count);
    ASSERT_EQ_SIZE(count, 4);
    ASSERT_EQ_STR(parts3[0], "one");
    ASSERT_EQ_STR(parts3[1], "two");
    ASSERT_EQ_STR(parts3[2], "three");
    ASSERT_EQ_STR(parts3[3], "four");
    guiarstr_split_free(parts3, count);
    
    // Split lines
    char** parts4 = guiarstr_split_lines("line1\nline2\r\nline3", &count);
    ASSERT_EQ_SIZE(count, 3);
    ASSERT_EQ_STR(parts4[0], "line1");
    ASSERT_EQ_STR(parts4[1], "line2");
    ASSERT_EQ_STR(parts4[2], "line3");
    guiarstr_split_free(parts4, count);
    
    SECTION("Join Tests");
    char* words[] = {"C", "is", "fun"};
    char* joined = guiarstr_join(words, 3, " ");
    ASSERT_EQ_STR(joined, "C is fun");
    free(joined);
    
    SECTION("Replace Tests");
    char* replaced = guiarstr_replace("the cat sat on the mat", "the", "a");
    ASSERT_EQ_STR(replaced, "a cat sat on a mat");
    free(replaced);
    
    // Replace with limit
    char* replaced2 = guiarstr_replace_n("the cat sat on the mat", "the", "a", 1);
    ASSERT_EQ_STR(replaced2, "a cat sat on the mat");
    free(replaced2);
    
    // Replace character
    char* replaced3 = guiarstr_replace_char("hello world", 'l', 'x');
    ASSERT_EQ_STR(replaced3, "hexxo worxd");
    free(replaced3);
    
    // Remove characters
    char* replaced4 = guiarstr_remove_chars("hello world", "lw");
    ASSERT_EQ_STR(replaced4, "heo ord");
    free(replaced4);
    
    SECTION("Reverse Tests");
    char* rev1 = guiarstr_reverse("abc");
    ASSERT_EQ_STR(rev1, "cba");
    free(rev1);
    
    char* rev2 = guiarstr_reverse("مرحبا");
    ASSERT_EQ_STR(rev2, "ابحرم");
    free(rev2);
    
    char* rev3 = guiarstr_reverse("okba😊dev");
    ASSERT_EQ_STR(rev3, "ved😊abko");
    free(rev3);
    
    SECTION("Contains / StartsWith / EndsWith");
    ASSERT_TRUE(guiarstr_contains("hello world", "world"));
    ASSERT_FALSE(guiarstr_contains("hello world", "mars"));
    ASSERT_TRUE(guiarstr_contains("abc", ""));
    
    ASSERT_TRUE(guiarstr_startswith("GuiarStr", "Guiar"));
    ASSERT_FALSE(guiarstr_startswith("GuiarStr", "Str"));
    ASSERT_TRUE(guiarstr_startswith("abc", ""));
    
    ASSERT_TRUE(guiarstr_endswith("GuiarStr", "Str"));
    ASSERT_FALSE(guiarstr_endswith("GuiarStr", "Guiar"));
    ASSERT_TRUE(guiarstr_endswith("abc", ""));
    
    SECTION("Case-insensitive Tests");
    ASSERT_TRUE(guiarstr_startswithi("GuiarStr", "guiar"));
    ASSERT_TRUE(guiarstr_endswithi("GuiarStr", "str"));
    
    SECTION("Count Tests");
    ASSERT_EQ_SIZE(guiarstr_count("abababab", "ab"), 4);
    ASSERT_EQ_SIZE(guiarstr_count("aaaaa", "aa"), 2);
    ASSERT_EQ_SIZE(guiarstr_count("nothing", "z"), 0);
    ASSERT_EQ_SIZE(guiarstr_count("abcabcabc", ""), 0);
    
    SECTION("Find Tests");
    ASSERT_EQ_SIZE(guiarstr_find("hello world", "world"), 6);
    ASSERT_EQ_SIZE(guiarstr_find("hello world", "mars"), (size_t)-1);
    ASSERT_EQ_SIZE(guiarstr_find_from("hello world hello", "hello", 6), 12);
    ASSERT_EQ_SIZE(guiarstr_rfind("hello world hello", "hello"), 12);
    ASSERT_EQ_SIZE(guiarstr_find_char("hello world", 'w'), 6);
    ASSERT_EQ_SIZE(guiarstr_rfind_char("hello world", 'l'), 9);
    ASSERT_EQ_SIZE(guiarstr_find_any("hello world", "ow"), 4);
    ASSERT_EQ_SIZE(guiarstr_find_not_any("hello world", "helo "), 6);
    
    SECTION("Dynamic String Tests");
    GuiarStr* str = guiarstr_create("hello");
    ASSERT_TRUE(str != NULL);
    ASSERT_EQ_STR(str->data, "hello");
    ASSERT_EQ_SIZE(str->length, 5);
    
    // Append
    GuiarStrError err = guiarstr_append(str, " world");
    ASSERT_EQ_ERR(err, GUIARSTR_OK);
    ASSERT_EQ_STR(str->data, "hello world");
    
    // Append char
    err = guiarstr_append_char(str, '!');
    ASSERT_EQ_ERR(err, GUIARSTR_OK);
    ASSERT_EQ_STR(str->data, "hello world!");
    
    // Insert
    err = guiarstr_insert(str, 5, " there");
    ASSERT_EQ_ERR(err, GUIARSTR_OK);
    ASSERT_EQ_STR(str->data, "hello there world!");
    
    // Remove
    err = guiarstr_remove(str, 5, 6);
    ASSERT_EQ_ERR(err, GUIARSTR_OK);
    ASSERT_EQ_STR(str->data, "hello world!");
    
    // Clear
    err = guiarstr_clear(str);
    ASSERT_EQ_ERR(err, GUIARSTR_OK);
    ASSERT_EQ_SIZE(str->length, 0);
    ASSERT_EQ_STR(str->data, "");
    
    guiarstr_free(str);
    
    SECTION("String Builder Tests");
    GuiarStrBuilder* builder = guiarstr_builder_create(16);
    ASSERT_TRUE(builder != NULL);
    
    err = guiarstr_builder_append(builder, "hello");
    ASSERT_EQ_ERR(err, GUIARSTR_OK);
    
    err = guiarstr_builder_append_char(builder, ' ');
    ASSERT_EQ_ERR(err, GUIARSTR_OK);
    
    err = guiarstr_builder_append(builder, "world");
    ASSERT_EQ_ERR(err, GUIARSTR_OK);
    
    GuiarStr* built = guiarstr_builder_build(builder);
    ASSERT_TRUE(built != NULL);
    ASSERT_EQ_STR(built->data, "hello world");
    
    guiarstr_free(built);
    guiarstr_builder_free(builder);
    
    SECTION("Formatting Tests");
    char* formatted = guiarstr_printf("%s %d %.2f", "test", 42, 3.14159);
    ASSERT_EQ_STR(formatted, "test 42 3.14");
    free(formatted);
    
    SECTION("Unicode/UTF-8 Tests");
    ASSERT_EQ_SIZE(guiarstr_utf8_len("hello"), 5);
    ASSERT_EQ_SIZE(guiarstr_utf8_len("مرحبا"), 5);
    ASSERT_EQ_SIZE(guiarstr_utf8_len("😊😊"), 2);
    
    ASSERT_EQ_SIZE(guiarstr_utf8_char_len("😊", 0), 4);
    ASSERT_EQ_SIZE(guiarstr_utf8_char_len("مرحبا", 0), 2);
    
    ASSERT_EQ_SIZE(guiarstr_utf8_byte_pos("مرحبا", 2), 4);
    
    ASSERT_TRUE(guiarstr_utf8_validate("hello"));
    ASSERT_TRUE(guiarstr_utf8_validate("مرحبا"));
    ASSERT_TRUE(guiarstr_utf8_validate("😊"));
    ASSERT_FALSE(guiarstr_utf8_validate("\xff"));
    
    ASSERT_EQ_SIZE(guiarstr_utf8_width("hello"), 5);
    ASSERT_EQ_SIZE(guiarstr_utf8_width("مرحبا"), 5);
    ASSERT_EQ_SIZE(guiarstr_utf8_width("😊"), 2);
    
    SECTION("Conversion Tests");
    bool success;
    int i = guiarstr_to_int("42", &success);
    ASSERT_TRUE(success);
    ASSERT_EQ_SIZE(i, 42);
    
    i = guiarstr_to_int("abc", &success);
    ASSERT_FALSE(success);
    
    char* from_int = guiarstr_from_int(42);
    ASSERT_EQ_STR(from_int, "42");
    free(from_int);
    
    double d = guiarstr_to_double("3.14159", &success);
    ASSERT_TRUE(success);
    ASSERT_TRUE(fabs(d - 3.14159) < 0.00001);
    
    char* from_double = guiarstr_from_double(3.14159, 2);
    ASSERT_EQ_STR(from_double, "3.14");
    free(from_double);
    
    printf("\n" GREEN " All tests passed successfully!" RESET "\n");
    printf("=============================================================\n");
    return 0;
}
