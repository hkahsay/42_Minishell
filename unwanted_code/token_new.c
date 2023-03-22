#include "../../headers/minishell.h"

static int get_token_len(char *token)
{
    int len = 0;
    while (token[len] != '\0' && token[len] != '>' && token[len] != '<' && token[len] != '|')
        len++;
    return len;
}


t_token	*create_list_token(char *line) //, int id no reason for id, it prints always the same id
{
	t_token	*token;
	t_token	*head;
	t_token	*temp;
	// t_token	*temp1;
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