typedef struct {
    token_type_t type;
    char value;
} token_t;

int main() {
    char str[] = "echo 'Hello, world!' "Goodbye, world!"";
    token_t tokens[100];
    int num_tokens = 0;
    int i = 0, j = 0;
    int in_single_quotes = 0, in_double_quotes = 0;

    // Parse the tokens from the string
    while (str[i]) {
        if (str[i] == '\'' && !in_double_quotes) {
            if (in_single_quotes) {
                tokens[num_tokens].type = TOKEN_SINGLE_QUOTE;
                tokens[num_tokens].value = malloc(sizeof(char) (j + 1));
                strncpy(tokens[num_tokens].value, str + i - j, j);
                tokens[num_tokens].value[j] = '\0';
                num_tokens++;
            }
            in_single_quotes = !in_single_quotes;
            i++;
            j = 0;
        }
        else if (str[i] == '"' && !in_single_quotes) {
            if (in_double_quotes) {
                tokens[num_tokens].type = TOKEN_DOUBLE_QUOTE;
                tokens[num_tokens].value = malloc(sizeof(char) * (j + 1));
                strncpy(tokens[num_tokens].value, str + i - j, j);
                tokens[num_tokens].value[j] = '\0';
                num_tokens++;
            }
            in_double_quotes = !in_double_quotes;
            i++;
            j = 0;
}
        else if (str[i] == ' ' && !in_single_quotes && !in_double_quotes) {
            if (j > 0) {
                tokens[num_tokens].type = TOKEN_WORD;
                tokens[num_tokens].value = malloc(sizeof(char) * (j + 1));
                strncpy(tokens[num_tokens].value, str + i - j, j);
                tokens[num_tokens].value[j] = '\0';
                num_tokens++;
                j = 0;
            }
            i++;
        }
        else {
            i++;
            j++;
        }
    }
    if (j > 0) {
        tokens[num_tokens].type = in_single_quotes ? TOKEN_SINGLE_QUOTE : in_double_quotes ? TOKEN_DOUBLE_QUOTE : TOKEN_WORD;
        tokens[num_tokens].value = malloc(sizeof(char) * (j + 1));
        strncpy(tokens[num_tokens].value, str + i - j, j);
        tokens[num_tokens].value[j] = '\0';
        num_tokens++;
    }

    // Print the tokens
    for (int k = 0; k < num_tokens; k++) {
        printf("Token %d: type=%d, value="%s"\n", k, tokens[k].type, tokens[k].value);
        free(tokens[k].value);
    }

    return 0;
}
