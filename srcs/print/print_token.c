#include "../../headers/minishell.h"

void print_token(t_token *temp)
{
	// int i = 0;

	// printf("i: %d\n", i);
	while (temp != NULL)
	{
		printf(MAR "TOKEN: %s = id[%d]\n" RS, temp->content, temp->id);
		temp = temp->next;
		// i++;
	}
	// printf("%d\n", i);
}

void	print_token_list(t_token *token_list)
{
	while (token_list != NULL)
	{
		if (token_list->id == TOK_PIPE)
			break;
		if (token_list->id == TOK_ERROR)
			break;	
		printf(OR "%s " RS, token_list->content);
		token_list = token_list->next;
	}
	printf("\n");
}

void	print_cmd_list1(t_token **cmd_list)
{
	int i = 0;
	while (cmd_list[i] != NULL)
	{
		printf("cmd %d:\n", i);
		print_token(cmd_list[i]);
		i++;
	}
}

void	print_tok_cmd_list(t_token **tok_cmd_list)
{
	int i = 0;
	while (tok_cmd_list[i] != NULL)
	{
		printf(GREEN "PIPE Command [%d] token list: " RS, i);
		print_token_list(tok_cmd_list[i]);
		i++;
	}
}

// void	print_array(char **array)
// {
// 	int	i = 0;

// 	while (array[i])
// 	{
// 		printf(OR "ARRAY PRINTING %s\n" RS, array[i]);
// 		i++;
// 	}
// }
