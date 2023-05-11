#include "../../headers/minishell.h"

t_token	*new_token(char *content, t_toktype type)
{
	t_token	*new_token;

	new_token = NULL;
	new_token = my_malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(content);
	new_token->id = type;
	new_token->next = NULL;
	return (new_token);
}
