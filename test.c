#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_spaces_around_char(char *str, char ch) {
    char *read_ptr = str;
    char *write_ptr = str;
    int in_target_char = 0;

    while (*read_ptr) {
        if (*read_ptr == ch) {
            in_target_char = 1;
            *write_ptr++ = *read_ptr++;
            while (isspace(*read_ptr)) {
                read_ptr++;
            }
        } else if (isspace(*read_ptr) && in_target_char) {
            read_ptr++;
        } else {
            *write_ptr++ = *read_ptr++;
            in_target_char = 0;
        }
    }

    *write_ptr = '\0'; // Null-terminate the string
}

int main() {
    char str[] = "  Hello ,  World   !  ";
    
    printf("Original string: \"%s\"\n", str);
    remove_spaces_around_char(str, ',');
    printf("Processed string: \"%s\"\n", str);

    return 0;
}
