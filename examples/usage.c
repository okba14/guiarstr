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




// usage.c - Example usage of the guiarstr library
// Compile with: gcc usage.c $(pkg-config --cflags --libs guiarstr) -o usage

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <guiarstr.h>

int main() {
    printf("=== GuiarStr Demo ===\n\n");
    
    // Basic operations
    printf("=== Basic Operations ===\n");
    
    // Trim example
    char text[] = "   GuiarStr is awesome!   ";
    printf("Original: \"%s\"\n", text);
    printf("Trimmed : \"%s\"\n\n", guiarstr_trim(text));
    
    // Strip example
    char strip_text[] = "***hello***";
    printf("Original: \"%s\"\n", strip_text);
    printf("Stripped : \"%s\"\n\n", guiarstr_strip(strip_text, "*"));
    
    // ToUpper / ToLower
    char str1[] = "GuiarStr";
    guiarstr_toupper(str1);
    printf("Upper: %s\n", str1);
    
    char str2[] = "GuiarStr";
    guiarstr_tolower(str2);
    printf("Lower: %s\n\n", str2);
    
    // Split and join
    printf("=== Split and Join ===\n");
    
    // Split with character delimiter
    size_t count;
    char** parts = guiarstr_split("lib,cli,test,doc", ',', &count);
    printf("Split result (%zu parts):\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("  - %s\n", parts[i]);
    }
    
    // Join
    char* joined = guiarstr_join(parts, count, " + ");
    printf("Joined: %s\n\n", joined);
    free(joined);
    guiarstr_split_free(parts, count);
    
    // Split with string delimiter
    char** parts2 = guiarstr_split_str("oneXYZtwoXYZthree", "XYZ", &count);
    printf("Split with string delimiter (%zu parts):\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("  - %s\n", parts2[i]);
    }
    guiarstr_split_free(parts2, count);
    
    // Split lines
    char** lines = guiarstr_split_lines("line1\nline2\r\nline3", &count);
    printf("\nSplit lines (%zu lines):\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("  - %s\n", lines[i]);
    }
    guiarstr_split_free(lines, count);
    
    // Replace
    printf("\n=== Replace ===\n");
    const char* sentence = "hello world, hello c!";
    char* replaced = guiarstr_replace(sentence, "hello", "hi");
    printf("Original: %s\n", sentence);
    printf("Replaced: %s\n", replaced);
    free(replaced);
    
    // Replace with limit
    char* replaced2 = guiarstr_replace_n(sentence, "hello", "hi", 1);
    printf("Limited replace: %s\n", replaced2);
    free(replaced2);
    
    // Replace character
    char* replaced3 = guiarstr_replace_char("hello world", 'l', 'x');
    printf("Replace char: %s\n", replaced3);
    free(replaced3);
    
    // Remove characters
    char* replaced4 = guiarstr_remove_chars("hello world", "lw");
    printf("Remove chars: %s\n\n", replaced4);
    free(replaced4);
    
    // Search
    printf("=== Search ===\n");
    const char* data = "the quick brown fox";
    printf("Text: %s\n", data);
    printf("Contains 'quick'? %s\n", guiarstr_contains(data, "quick") ? "Yes" : "No");
    printf("Contains 'slow'?  %s\n", guiarstr_contains(data, "slow") ? "Yes" : "No");
    printf("Starts with 'the'? %s\n", guiarstr_starts_with(data, "the") ? "Yes" : "No");
    printf("Ends with 'fox'?  %s\n", guiarstr_ends_with(data, "fox") ? "Yes" : "No");
    printf("Find 'brown' at position: %zu\n", guiarstr_find(data, "brown"));
    printf("Find 'o' from position 10: %zu\n", guiarstr_find_char_from(data, 'o', 10));
    printf("Find any of 'xyz': %zu\n", guiarstr_find_any(data, "xyz"));
    printf("Count 'o': %zu\n\n", guiarstr_count(data, "o"));
    
    // Case-insensitive search
    printf("=== Case-insensitive Search ===\n");
    const char* file = "report.pdf";
    printf("File: %s\n", file);
    printf("iStarts with 'ReP'? %s\n", guiarstr_starts_withi(file, "ReP") ? "Yes" : "No");
    printf("iEnds with '.PDF'?  %s\n\n", guiarstr_ends_withi(file, ".PDF") ? "Yes" : "No");
    
    // Unicode/UTF-8
    printf("=== Unicode/UTF-8 ===\n");
    const char* word = "مرحبا 😊";
    printf("Original: %s\n", word);
    printf("UTF-8 length: %zu characters\n", guiarstr_utf8_len(word));
    printf("UTF-8 byte length: %zu bytes\n", strlen(word));
    printf("UTF-8 display width: %zu columns\n", guiarstr_utf8_width(word));
    
    char* rev = guiarstr_reverse(word);
    printf("Reversed: %s\n", rev);
    free(rev);
    
    // UTF-8 substring
    char* substr = guiarstr_utf8_substring(word, 2, 2);
    printf("Substring [2:4]: %s\n", substr);
    free(substr);
    
    // UTF-8 validation
    printf("Valid UTF-8? %s\n", guiarstr_utf8_validate(word) ? "Yes" : "No");
    printf("Invalid UTF-8? %s\n\n", guiarstr_utf8_validate("\xff") ? "Yes" : "No");
    
    // Dynamic strings
    printf("=== Dynamic Strings ===\n");
    GuiarStr* dyn_str = guiarstr_create("hello");
    printf("Created: %s\n", dyn_str->data);
    
    GuiarStrError err = guiarstr_append(dyn_str, " world");
    printf("Append 'world': %s (error: %s)\n", dyn_str->data, guiarstr_error_message(err));
    
    err = guiarstr_append_char(dyn_str, '!');
    printf("Append '!': %s (error: %s)\n", dyn_str->data, guiarstr_error_message(err));
    
    err = guiarstr_insert(dyn_str, 5, " there");
    printf("Insert ' there': %s (error: %s)\n", dyn_str->data, guiarstr_error_message(err));
    
    err = guiarstr_remove(dyn_str, 5, 6);
    printf("Remove [5:11]: %s (error: %s)\n", dyn_str->data, guiarstr_error_message(err));
    
    guiarstr_free(dyn_str);
    
    // String builder
    printf("\n=== String Builder ===\n");
    GuiarStrBuilder* builder = guiarstr_builder_create(16);
    
    guiarstr_builder_append(builder, "hello");
    guiarstr_builder_append_char(builder, ' ');
    guiarstr_builder_append(builder, "world");
    guiarstr_builder_append_fmt(builder, " %d %.2f", 42, 3.14);
    
    GuiarStr* built = guiarstr_builder_build(builder);
    printf("Built: %s\n", built->data);
    
    guiarstr_free(built);
    guiarstr_builder_free(builder);
    
    // Formatting
    printf("\n=== Formatting ===\n");
    char* formatted = guiarstr_printf("%s %d %.2f", "test", 42, 3.14159);
    printf("Formatted: %s\n", formatted);
    free(formatted);
    
    // Conversion
    printf("\n=== Conversion ===\n");
    bool success;
    int i = guiarstr_to_int("42", &success);
    printf("String '42' to int: %d (success: %s)\n", i, success ? "Yes" : "No");
    
    double d = guiarstr_to_double("3.14159", &success);
    printf("String '3.14159' to double: %f (success: %s)\n", d, success ? "Yes" : "No");
    
    char* from_int = guiarstr_from_int(42);
    printf("Int 42 to string: %s\n", from_int);
    free(from_int);
    
    char* from_double = guiarstr_from_double(3.14159, 2);
    printf("Double 3.14159 to string: %s\n", from_double);
    free(from_double);
    
    // File operations
    printf("\n=== File Operations ===\n");
    GuiarStrError error;
    GuiarStr* file_content = guiarstr_read_file("usage.c", &error);
    if (file_content) {
        printf("Read file successfully (%zu bytes)\n", file_content->length);
        
        // Write to a new file
        error = guiarstr_write_file("usage_copy.c", file_content->data, false);
        printf("Write file: %s\n", guiarstr_error_message(error));
        
        guiarstr_free(file_content);
    } else {
        printf("Failed to read file: %s\n", guiarstr_error_message(error));
    }
    
    return 0;
}
