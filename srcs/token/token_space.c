#include "../../headers/minishell.h"

void *delete_tok_spaces(t_token **token_head)
{
    t_token *curr = *token_head;
    t_token *prev = NULL;
	t_token *temp;

    while (curr != NULL)
    {
        if (curr->id == TOK_SPACE)
        {
            if (prev != NULL)
                prev->next = curr->next;
            else
                *token_head = curr->next;
            temp = curr;
            curr = curr->next;
            free(temp->content);
            free(temp);
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
	return (0);
}
