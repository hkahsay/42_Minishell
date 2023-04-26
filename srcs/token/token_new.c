#include "../../headers/minishell.h"

t_token *new_token(char *content, t_toktype type)
{
	t_token *new_token;

	new_token = my_malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(content);
	// printf("new_token->content: %s\n", new_token->content);
	new_token->id = type;
	// printf("new_token->id: %d\n", new_token->id);
	// new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}
