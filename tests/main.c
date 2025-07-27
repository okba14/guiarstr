#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/guiarstr.h"

#define ASSERT_EQ_STR(actual, expected) \
    if (strcmp(actual, expected) != 0) { \
        fprintf(stderr, "[FAIL] \"%s\" != \"%s\" (line %d)\n", actual, expected, __LINE__); \
        exit(1); \
    } else { \
        printf("[PASS] \"%s\"\n", actual); \
    }

#define ASSERT_EQ_SIZE(actual, expected) \
    if ((actual) != (expected)) { \
        fprintf(stderr, "[FAIL] %zu != %zu (line %d)\n", actual, expected, __LINE__); \
        exit(1); \
    } else { \
        printf("[PASS] %zu\n", actual); \
    }

#define ASSERT_TRUE(expr) \
    if (!(expr)) { \
        fprintf(stderr, "[FAIL] ASSERT_TRUE failed (line %d)\n", __LINE__); \
        exit(1); \
    } else { \
        printf("[PASS] ASSERT_TRUE\n"); \
    }

#define ASSERT_FALSE(expr) \
    if (expr) { \
        fprintf(stderr, "[FAIL] ASSERT_FALSE failed (line %d)\n", __LINE__); \
        exit(1); \
    } else { \
        printf("[PASS] ASSERT_FALSE\n"); \
    }

int main(void) {
    printf("Running GuiarStr tests...\n\n");

    // === Trim ===
    char trim1[] = "  hello world  ";
    ASSERT_EQ_STR(guiarstr_trim(trim1), "hello world");

    char trim2[] = "   ";
    ASSERT_EQ_STR(guiarstr_trim(trim2), "");

    // === Split ===
    size_t count;
    char** parts = guiarstr_split("one,two,three", ',', &count);
    ASSERT_EQ_SIZE(count, (size_t)3);
    ASSERT_EQ_STR(parts[0], "one");
    ASSERT_EQ_STR(parts[1], "two");
    ASSERT_EQ_STR(parts[2], "three");
    guiarstr_split_free(parts, count);

    // === Replace ===
    char* replaced = guiarstr_replace("the cat sat on the mat", "the", "a");
    ASSERT_EQ_STR(replaced, "a cat sat on a mat");
    free(replaced);

    // === ToLower ===
    char lower[] = "HeLLo GUIAR";
    guiarstr_tolower(lower);
    ASSERT_EQ_STR(lower, "hello guiar");

    // === ToUpper ===
    char upper[] = "guiarStr";
    guiarstr_toupper(upper);
    ASSERT_EQ_STR(upper, "GUIARSTR");

    // === StartsWith ===
    ASSERT_TRUE(guiarstr_startswith("GuiarStr", "Guiar"));
    ASSERT_FALSE(guiarstr_startswith("GuiarStr", "Str"));
    ASSERT_TRUE(guiarstr_startswith("abc", ""));

    // === Strip ===
    char strip1[] = "***hello***";
    ASSERT_EQ_STR(guiarstr_strip(strip1, "*"), "hello");

    char strip2[] = "!!abc!!";
    ASSERT_EQ_STR(guiarstr_strip(strip2, "!"), "abc");

    char strip3[] = "><><okba><>";
    ASSERT_EQ_STR(guiarstr_strip(strip3, "><"), "okba");

    // === Join ===
    char* words[] = {"C", "is", "fun"};
    char* joined = guiarstr_join(words, 3, " ");
    ASSERT_EQ_STR(joined, "C is fun");
    free(joined);

    printf("\nAll tests passed successfully!\n");
    return 0;
}
