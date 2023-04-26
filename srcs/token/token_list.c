#include "../../headers/minishell.h"

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

void	add_token(t_token **head, char *content, t_toktype type)
{
	t_token *token;
	t_token *curr;

	curr = NULL;
	token = new_token(content, type);
	// if (!token)
	// 	return (0);
	if (*head == NULL)
		*head = token;
	else
	{
		curr = *head;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = token;
		// token->prev = curr;
		token->next = NULL;
	}
}

t_token *last_token(t_token *token_list)
{
	t_token	*curr;

	if (token_list == NULL)
		return (NULL);
	curr = token_list;
	while (curr->next != NULL)
		curr = curr->next;
	return (curr);
}


