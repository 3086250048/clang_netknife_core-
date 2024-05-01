#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_spaces_around_char(char *str, char ch) {
    char *read_ptr = str;
    char *write_ptr = str;
    int found_char = 0;

    while (*read_ptr) {
        if (*read_ptr == ch) {
            // Found the target char, remove spaces before it
            while (write_ptr > str && isspace(*(write_ptr - 1)) && (*(write_ptr - 1) != '\n')) {
                write_ptr--;
            }
            found_char = 1;
            *write_ptr++ = *read_ptr++;
            // Remove trailing spaces
            while (isspace(*read_ptr) && (*read_ptr != '\n')) {
                read_ptr++;
            }
        } else {
            // Copy non-target characters
            *write_ptr++ = *read_ptr++;
        }
    }

    *write_ptr = '\0'; // Null-terminate the string
}

int main() {
    char str[] = "  Hello \n my \n name \n  World   !  ";
    
    printf("Original string: \"%s\"\n", str);
    remove_spaces_around_char(str, '\n');
    printf("Processed string: \"%s\"\n", str);

    return 0;
}

