#include "../../headers/minishell.h"

t_list	*init_token(t_list	*token)
{
	token = malloc(sizeof(t_list) * 1);
	if (!token)
		return (0);
	token->content = NULL;
	token->id_token = 0;
	token->next = NULL;
	return (token);
}

static int get_token_len(char *token)
{
    int len = 0;
    while (token[len] != '\0' && token[len] != '>' && token[len] != '<' && token[len] != '|')
        len++;
    return len;
}


t_list	*create_list_token(char *line) //, int id no reason for id, it prints always the same id
{
	t_list	*token;
	t_list	*head;
	t_list	*temp;
	// t_list	*temp1;
	int		i;

	i = 0;
	token = NULL;
	head = NULL;
	temp = NULL;
	if (!line)
		return (0);
	while (line[i])
	{
		
	}
	print_token(token);	
	printf("i after token creation: %d\n", i);	
	return (head);	
}		