#include "../../headers/minishell.h"

int ft_count_pipes(t_token **tok_head)
{
	t_token *tok_h;
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

int	ft_token_list_size(t_token **tok_head)
{
	t_token *tok_h;
	int		size;

	tok_h = *tok_head;
	size = 0;
	while (tok_h != NULL)
	{
		if (tok_h != NULL)
			size++;
		tok_h = tok_h->next;
	}
	return (size);
}

void	ft_token_list_addback(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
