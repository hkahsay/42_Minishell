#include "../../headers/minishell.h"

void free_token_list(t_token *tokens)
{
    t_token *current = tokens;

    while (current != NULL)
    {
        t_token *next = current->next;
        free(current->content);
        free(current);
        current = next;
    }
}
