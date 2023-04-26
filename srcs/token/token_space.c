#include "../../headers/minishell.h"

void *delete_tok_spaces(t_token **token_head)
{
	t_token *curr;
	t_token *prev;
	t_token *temp;

	curr = *token_head;
	prev = NULL;
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
			my_free(temp->content);
			my_free(temp);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return (0);
}
