#include "../../headers/minishell.h"

// static void free_token(t_token *token)
// {
//     if (token)
//     {
//         my_free(token->content);
//         token->content = NULL;
//         my_free(token);
//         token = NULL;
//     }
// }

t_token *new_token(char *content, t_toktype type)
{
	t_token *token_new;

	token_new = my_malloc(sizeof(t_token));
	if (!token_new)
		return (NULL);
	token_new->content = ft_strdup(content);
	// printf("token_new->content: %s\n", token_new->content);
	token_new->id = type;
	// printf("token_new->id: %d\n", token_new->id);
	// token_new->prev = NULL;
	token_new->next = NULL;
	// free_token(token_new);
	return (token_new);
}

