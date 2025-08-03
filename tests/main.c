#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/guiarstr.h"

// === Colors and symbols ===
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"
#define CHECK   "\xE2\x9C\x94"  // ✔
#define CROSS   "\xE2\x9C\x98"  // ✘

#define SECTION(title) \
    printf("\n" CYAN "==[ %s ]%.*s\n" RESET, title, 58 - (int)strlen(title), "==================================================");

#define ASSERT_EQ_STR(actual, expected) \
    if (strcmp(actual, expected) != 0) { \
        fprintf(stderr, RED "[%s] \"%s\" != \"%s\" (line %d)\n" RESET, CROSS, actual, expected, __LINE__); \
        exit(1); \
    } else { \
        printf(GREEN "[%s] %-22s\"%s\"\n" RESET, CHECK, "", actual); \
    }

#define ASSERT_EQ_SIZE(actual, expected) \
    if ((actual) != (expected)) { \
        fprintf(stderr, RED "[%s] %zu != %zu (line %d)\n" RESET, CROSS, (size_t)(actual), (size_t)(expected), __LINE__); \
        exit(1); \
    } else { \
        printf(GREEN "[%s] %-22s%zu == %zu (line %d)\n" RESET, CHECK, "", (size_t)(actual), (size_t)(expected), __LINE__); \
    }

#define ASSERT_TRUE(expr) \
    if (!(expr)) { \
        fprintf(stderr, RED "[%s] ASSERT_TRUE failed (line %d)\n" RESET, CROSS, __LINE__); \
        exit(1); \
    } else { \
        printf(GREEN "[%s] ASSERT_TRUE\n" RESET, CHECK); \
    }

#define ASSERT_FALSE(expr) \
    if (expr) { \
        fprintf(stderr, RED "[%s] ASSERT_FALSE failed (line %d)\n" RESET, CROSS, __LINE__); \
        exit(1); \
    } else { \
        printf(GREEN "[%s] ASSERT_FALSE\n" RESET, CHECK); \
    }

int main(void) {
    printf("\n==================== GuiarStr Test Suite ====================\n");

    SECTION("Trim Tests");
    char trim1[] = "  hello world  ";
    ASSERT_EQ_STR(guiarstr_trim(trim1), "hello world");
    char trim2[] = "   ";
    ASSERT_EQ_STR(guiarstr_trim(trim2), "");

    SECTION("Split Tests");
    size_t count;
    char** parts = guiarstr_split("one,two,three", ',', &count);
    ASSERT_EQ_SIZE(count, 3);
    ASSERT_EQ_STR(parts[0], "one");
    ASSERT_EQ_STR(parts[1], "two");
    ASSERT_EQ_STR(parts[2], "three");
    guiarstr_split_free(parts, count);

    SECTION("Replace Tests");
    char* replaced = guiarstr_replace("the cat sat on the mat", "the", "a");
    ASSERT_EQ_STR(replaced, "a cat sat on a mat");
    free(replaced);

    SECTION("ToLower / ToUpper / Strip");
    char lower[] = "HeLLo GUIAR";
    guiarstr_tolower(lower);
    ASSERT_EQ_STR(lower, "hello guiar");

    char upper[] = "guiarStr";
    guiarstr_toupper(upper);
    ASSERT_EQ_STR(upper, "GUIARSTR");

    char strip1[] = "***hello***";
    ASSERT_EQ_STR(guiarstr_strip(strip1, "*"), "hello");
    char strip2[] = "!!abc!!";
    ASSERT_EQ_STR(guiarstr_strip(strip2, "!"), "abc");
    char strip3[] = "><><okba><>";
    ASSERT_EQ_STR(guiarstr_strip(strip3, "><"), "okba");

    SECTION("Join Tests");
    char* words[] = {"C", "is", "fun"};
    char* joined = guiarstr_join(words, 3, " ");
    ASSERT_EQ_STR(joined, "C is fun");
    free(joined);

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

    SECTION("Count Tests");
    ASSERT_EQ_SIZE(guiarstr_count("abababab", "ab"), 4);
    ASSERT_EQ_SIZE(guiarstr_count("aaaaa", "aa"), 2);
    ASSERT_EQ_SIZE(guiarstr_count("nothing", "z"), 0);
    ASSERT_EQ_SIZE(guiarstr_count("abcabcabc", ""), 0);

    printf("\n" GREEN " All tests passed successfully!" RESET "\n");
    printf("=============================================================\n");
    return 0;
}
