
#include "../../headers/minishell.h"

void print_token(t_token *temp)
{
	int i = 0;

	printf("i: %d\n", i);
	while (temp)
	{
		printf("TOKEN: %s=%d\n", temp->content, temp->id);
		temp = temp->next;
		i++;
	}
	printf("%d\n", i);
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
