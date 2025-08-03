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
    printf("Lower: %s\n\n", str2);

    // StartsWith / EndsWith
    const char* file = "report.pdf";
    printf("Starts with 'rep'? %s\n", guiarstr_starts_with(file, "rep") ? "Yes" : "No");
    printf("Ends with '.pdf'?  %s\n\n", guiarstr_ends_with(file, ".pdf") ? "Yes" : "No");

    // Case-insensitive versions
    printf("iStarts with 'ReP'? %s\n", guiarstr_starts_withi(file, "ReP") ? "Yes" : "No");
    printf("iEnds with '.PDF'?  %s\n\n", guiarstr_ends_withi(file, ".PDF") ? "Yes" : "No");

    // Reverse UTF-8-safe
    const char* word = "مرحبا 😊";
    char* rev = guiarstr_reverse(word);
    printf("Original: %s\n", word);
    printf("Reversed: %s\n\n", rev);
    free(rev);

    // Contains
    const char* data = "the quick brown fox";
    printf("Contains 'quick'? %s\n", guiarstr_contains(data, "quick") ? "Yes" : "No");
    printf("Contains 'slow'?  %s\n\n", guiarstr_contains(data, "slow") ? "Yes" : "No");

    // Count occurrences
    printf("Count 'ab' in 'abababab': %zu\n", guiarstr_count("abababab", "ab"));
    printf("Count 'aa' in 'aaaaa': %zu\n", guiarstr_count("aaaaa", "aa"));
    printf("Count 'z' in 'nothing': %zu\n\n", guiarstr_count("nothing", "z"));

    return 0;
}
