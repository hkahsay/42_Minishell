#include "../../headers/minishell.h"

char *strndup(const char *str, size_t n) {
    char *copy;

    /* Get the length of the input string */
    size_t len = strlen(str);

    /* Allocate memory for the copy */
    copy = malloc(n + 1);

    /* Copy the string */
    strncpy(copy, str, n);
    copy[n] = '\0';

    return copy;
}
