#include "../../headers/minishell.h"

t_token *new_token(char *content, t_toktype type)
{
	t_token *new_token = NULL;

	new_token = my_malloc(sizeof(t_token));
	// new_token = init_token(new_token);
	printf(R "new_token %p \n" RS, new_token);
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(content);
	printf(GREEN "new_token->content [%p] %s \n" RS, new_token->content, new_token->content);
	// free(content);
	// printf("new_token->content: %s\n", new_token->content);
	new_token->id = type;
	// printf("new_token->id: %d\n", new_token->id);
	// new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}
