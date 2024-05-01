#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void append_string(char **dest, const char *src) {
    size_t dest_len = strlen(*dest);
    size_t src_len = strlen(src);
    
    // Reallocate memory for destination string
    *dest = (char *)realloc(*dest, dest_len + src_len + 1); // +1 for null terminator
    if (*dest == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Append source string to destination string
    strcpy(*dest + dest_len, src);
}

int main() {
    char *str = malloc(sizeof(char) * 10); // Allocate initial memory
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(str, "Hello");

    printf("Original string: \"%s\"\n", str);
    
    // Append additional content
    append_string(&str, ", World!");

    printf("Appended string: \"%s\"\n", str);

    free(str); // Don't forget to free allocated memory

    return 0;
}

