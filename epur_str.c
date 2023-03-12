#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *epur_str(char *str)
{
    char *result = malloc(strlen(str) + 1); // allocate memory for the result string
    char *p = result;
    int space_flag = 0;

	if (!str)
		return (0); // to check what we have to return here
    // skip leading spaces
    while (isspace(*str)) {
        str++;
    }

    // copy string with exactly one space between words
    while (*str != '\0') {
        if (isspace(*str)) {
            if (!space_flag) {
                *p++ = ' ';
                space_flag = 1;
            }
        } else {
            *p++ = *str;
            space_flag = 0;
        }
        str++;
    }

    // remove trailing space
    if (space_flag && p > result) {
        p--;
    }

    // add null terminator
    *p = '\0';

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }
    char *result = epur_str(argv[1]);
    printf("%s", result);
    free(result);
    return 0;
}
