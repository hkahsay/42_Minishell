#include "../../headers/minishell.h"

t_token	*init_token(t_token	*token)
{
	token = my_malloc(sizeof(t_token) * 1);
	if (!token)
		return (0);
	token->content = NULL;
	token->id = 0;
	token->next = NULL;
	return (token);
}
