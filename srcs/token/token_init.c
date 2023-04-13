
#include "../../headers/minishell.h"

void add_token(t_token **head, char *content, t_toktype type)
{
    t_token *token = new_token(content, type);

	// if (!token)
	// 	return (0);
    if (*head == NULL)
    {
        *head = token;
    }
    else
    {
		t_token *current = *head;
		while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = token;
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

t_token *new_token(char *content, t_toktype type)
{
    t_token *new_token;

    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return (NULL);
    new_token->content = ft_strdup(content);
    printf("new_token->content: %s\n", new_token->content);
    new_token->id = type;
    printf("new_token->id: %d\n", new_token->id);
    new_token->next = NULL;
    return (new_token);
}

t_token	*init_token(t_token	*token)
{
	token = malloc(sizeof(t_token) * 1);
	if (!token)
		return (0);
	token->content = NULL;
	token->id = 0;
	token->next = NULL;
	return (token);
}
