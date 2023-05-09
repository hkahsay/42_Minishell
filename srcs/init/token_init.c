#include "../../headers/minishell.h"

t_token	*init_token(t_token	*token)
{
	token = my_malloc(sizeof(t_token) * 1);
	printf(OR "token %p \n" RS, token);
	if (!token)
		return (0);
	token->content = NULL;
	token->id = 0;
	// token->prev = NULL;
	token->next = NULL;
	return (token);
}
