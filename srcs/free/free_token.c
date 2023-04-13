#include "../../headers/minishell.h"

void	free_token_list(t_token *tokens)
{
	t_token *cur;
	t_token *next;

	cur = tokens;
	next = NULL;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur->content);
		free(cur);
		cur = next;
	}
}
