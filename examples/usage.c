// usage.c - Example usage of the guiarstr library
// Compile with: gcc usage.c $(pkg-config --cflags --libs guiarstr) -o usage

#include <stdio.h>
#include <stdlib.h>
#include <guiarstr.h>

int main() {
    printf("=== GuiarStr Demo ===\n\n");

    // Trim example
    char text[] = "   GuiarStr is awesome!   ";
    printf("Original: \"%s\"\n", text);
    printf("Trimmed : \"%s\"\n\n", guiarstr_trim(text));

    // Split example
    size_t count;
    char** parts = guiarstr_split("lib,cli,test,doc", ',', &count);
    printf("Split result (%zu parts):\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("  - %s\n", parts[i]);
    }
    guiarstr_split_free(parts, count);
    printf("\n");

    // Replace example
    const char* sentence = "hello world, hello c!";
    char* replaced = guiarstr_replace(sentence, "hello", "hi");
    printf("Original: %s\n", sentence);
    printf("Replaced: %s\n", replaced);
    free(replaced);
    printf("\n");

    // ToUpper / ToLower
    char str1[] = "GuiarStr";
    guiarstr_toupper(str1);
    printf("Upper: %s\n", str1);

    char str2[] = "GuiarStr";
    guiarstr_tolower(str2);
    printf("Lower: %s\n", str2);

    return 0;
}
