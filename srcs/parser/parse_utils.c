#include "../../headers/minishell.h"

int	ft_count_pipes(t_token **tok_head)
{
	t_token	*tok_h;
	int		size;

	tok_h = *tok_head;
	size = 0;
	while (tok_h != NULL)
	{
		if (tok_h != NULL && tok_h->id == TOK_PIPE)
			size++;
		tok_h = tok_h->next;
	}
	return (size);
}
