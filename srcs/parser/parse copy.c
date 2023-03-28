#include "../../headers/minishell.h"

static t_redir_args	*init_args(t_redir_args *new_redir_args)
{
	new_redir_args = malloc(sizeof(t_redir_args) * 1);
	if (!new_redir_args)
		return (NULL);
	new_redir_args->type = 0;
	new_redir_args->args = NULL;
	return (new_redir_args);
}

static t_cmd	*init_cmd(void)
{
	t_cmd	*new_cmd;
	
	new_cmd = malloc(sizeof(t_cmd) * 1);
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd_args = NULL;
	new_cmd->cmd_redir = NULL;
	return (new_cmd);
}

// // static t_redir_args *new_cmd(char *content, t_toktype type)
// // {
// //     // t_cmd_node *new_cmds = NULL;
// // 	new_cmds = init_cmds(new_cmds);

// //     // new_cmds = malloc(sizeof(t_cmd));
// //     // if (!new_cmds)
// //     //     return (NULL);
// //     new_cmds->cmd_args = ft_strdup(content);
// //     new_cmds->cmd_redir = type;
// //     return (new_cmds);
// // }

static t_redir_args *new_redir_args(char *content, t_toktype type)
{
    t_redir_args *new_args = NULL;
	new_args = init_args(new_args);

    // new_args = malloc(sizeof(t_redir_args));
    // if (!new_args)
    //     return (NULL);
    new_args->args = ft_strdup(content);
    new_args->type = type;
    new_args->next = NULL;
    return (new_args);
}

// t_token *new_token(char *content, t_toktype type)
// {
//     t_token *new_token;

//     new_token = malloc(sizeof(t_token));
//     if (!new_token)
//         return (NULL);
//     new_token->content = ft_strdup(content);
//     new_token->id = type;
//     new_token->next = NULL;
//     return (new_token);
// }

void print_t_redir_args(t_redir_args *temp)
{
	int i = 0;

	while (temp)
	{
		temp = temp->next;
		i++;
	}
}

static t_redir_args *add_args_to_list(t_redir_args **head_args, int type, char *content) //t_redir_args *args, t_token *head, 
{
	t_redir_args *temp = NULL;

   
    t_redir_args *args = new_redir_args(content, type);

    if (*head_args == NULL)
    {
        *head_args = args;
    }
    else
    {
        t_redir_args *current = *head_args;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = args;
    }
	temp = *head_args;
	print_t_redir_args(temp);
	return (*head_args);
}

static void	eval_token(t_token *head, t_cmd **cmd)
{
	// int		i;
	// int	counter;
	t_redir_args *args = NULL;
	//t_redir_args *redir = NULL;
	t_token *head_ptr = NULL;
	// t_token *temp = NULL;
	*cmd = init_cmd();
	int i = 2;
	int j = 0;
	
	// args = init_args(args);
	head_ptr = head;
	printf("1\n");
	while (head_ptr && (t_toktype)(head->id) != TOK_PIPE)
	{
		printf("2\n");
		if (head_ptr->id == TOK_WORD || head_ptr->id == TOK_D_QUOTE || head_ptr->id == TOK_S_QUOTE) //(head_ptr->id != TOK_PIPE)
		{
			printf("3\n");
			while (head_ptr && (head_ptr->id == TOK_WORD || head_ptr->id == TOK_D_QUOTE || head_ptr->id == TOK_S_QUOTE)) // || head_ptr->id == TOK_DOLLAR
			{
				printf("4\n");
				// if tok dollar
				// convertir 
				(*cmd)->cmd_args = add_args_to_list(&args, head_ptr->id, head_ptr->content); //&head, 
				while((*cmd)->cmd_args)
				{
					printf(OR "WORD list[%d]: %d %s, ", j, (*cmd)->cmd_args->type, (*cmd)->cmd_args->args);
					(*cmd)->cmd_args = (*cmd)->cmd_args->next;
					j++;
				}
				printf("\n");
				if (head_ptr && (head_ptr->id == TOK_REDIR_IN || head_ptr->id == TOK_REDIR_OUT || head_ptr->id == TOK_REDIR_OUT_APPEND ||
					head_ptr->id == TOK_HEREDOC))
				{
					printf("4a break");
					break;
				}
				printf("\n"RS);
				if (head_ptr && head_ptr->next)
					head_ptr = head_ptr->next;
				else
				{
					printf("5\n");
					return ;
				}
			}
		}
			if (head_ptr && (head_ptr->id == TOK_REDIR_IN || head_ptr->id == TOK_REDIR_OUT || head_ptr->id == TOK_REDIR_OUT_APPEND ||
				head_ptr->id == TOK_HEREDOC)) // && (head_ptr->next && head_ptr->next->id == TOK_WORD)
			{
				printf("6\n");

				if (head_ptr->next && head_ptr->next->id == TOK_WORD)
				{
					printf("7\n");
					while (i > 0)
					{
						(*cmd)->cmd_redir = add_args_to_list(&args, head_ptr->id, head_ptr->content);
						i--;
					}
					while((*cmd)->cmd_args)
					{
						printf(OR "WORD list: %d %s, ", (*cmd)->cmd_args->type, (*cmd)->cmd_args->args);
						(*cmd)->cmd_args = (*cmd)->cmd_args->next;
					}
					printf("\n");
					printf("8\n");
				}
				// else
				// {
				// 	printf("9\n");
				// }
				printf("10\n");
			}
			else if (head_ptr->id == TOK_ERRQUOTE)
			{
				printf("11\n");
				exit (0);
			}
			printf("12\n");
		// }
		// else
		printf("13\n");
		printf("Head content: %s\n", head_ptr->content);
		head_ptr = head_ptr->next;
		printf("Next: %p\n", head_ptr);
		printf("14\n");
	}
	printf("15\n");
	// return (cmd);
}

t_cmd	*parse(t_token *head)
{
	t_cmd	*cmd = NULL;
	// t_cmd	*temp_cmd = NULL;
	t_token *temp = head;
	// t_cmd_node	*single_cmd;

	
	if (head && (t_toktype)(head->id) != TOK_PIPE)
		eval_token(head, &cmd);
	printf("cmd address %p\n", cmd);
	// printf(GREEN "WORD list: %d %s, ", cmd->cmd_args->type, cmd->cmd_args->args);
	// temp_cmd = cmd;
	// printf("temp_cmd address %p\n", temp_cmd->cmd_args);	
	// while(temp_cmd)
	// {
	// 	printf(GREEN "WORD list: %d %s, ", temp_cmd->cmd_args->type, temp_cmd->cmd_args->args);
	// 	temp_cmd->cmd_args = temp_cmd->cmd_args->next;
	// }	
	execute(cmd);
	print_token(temp);
	// if (!head)
	// 	return (NULL);
	// token_analysis(head, eval_token);
	return (cmd);
}
