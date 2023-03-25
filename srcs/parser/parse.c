#include "../../headers/minishell.h"

// static t_cmd_node *build_cmd_from_token_word(t_cmd_node *build_cmd, int *n, char *token_content)
// {
// 	// char	*cmd_str;
// 	int		i;

// 	i = 0;
// 	build_cmd->cmd_args = ft_split(token_content, ' ');
// 	while(build_cmd->cmd_args[i])
// 	{
// 		printf(YELLOW "token_content %s\n", build_cmd->cmd_args[i]);
// 		i++;
// 	}
// 	return (build_cmd);
// }

static t_cmd_redir	*init_redir(t_cmd_redir *new_cmd_redir)
{
	new_cmd_redir = malloc(sizeof(t_cmd_redir) * 1);
	if (!new_cmd_redir)
		return (NULL);
	new_cmd_redir->type = 0;
	new_cmd_redir->str = NULL;
	return (new_cmd_redir);
}

static t_cmd_node	*init_cmd(t_cmd_node *new_cmd, int size)
{
	// t_cmd_node	*new_cmd;
	// t_cmd_redir *new_cmd_red;

	// new_cmd_red = NULL;
	// int i;

	
	new_cmd = malloc(sizeof(t_cmd_node) * 1);
	if (!new_cmd)
		return (NULL);
	printf(R "hello from init_cmd: size oflist for malloc **cmd_args %d\n" RS, size);	
	new_cmd->cmd_args = malloc(sizeof(char *) * (size + 1));
	new_cmd->cmd_args[size] = NULL;
	printf(R "hello from init_cmd: new_cmd->cmd_args address %p\n" RS, new_cmd->cmd_args);
	if (!new_cmd->cmd_args)
		return (0);
	// i = 0;	
	// while (new_cmd->cmd_args[i] && i < size)
	// {
	// 	printf(R "hello from init_cmd: new_cmd->cmd_args address %p\n" RS, new_cmd->cmd_args[i]);
	// 	i++;
	// } 
		
	if (!new_cmd->cmd_args)
		return (0);
	new_cmd->cmd_redir = init_redir(new_cmd->cmd_redir);
	return (new_cmd);	
}

static void    token_analysis(t_token *head, void (*f)(t_toktype *, char **, int *))
{
	t_token		*head_ptr;
	int			cmd_list_size;

	head_ptr = head;
	cmd_list_size = 0;
	print_token(head_ptr);
	while (head_ptr)
	{
		// cmd_list_size++;
		// cmd_list_size = 0;
		while (head_ptr != NULL && head_ptr->id != TOK_PIPE)
		{
			cmd_list_size++;
			head_ptr = head_ptr->next;
		}
		printf(GGREEN "list size before pipe: %d\n" RS, cmd_list_size);
		head_ptr = head;
		(*f)(&head_ptr->id, &head_ptr->content, &cmd_list_size);
		printf(R "token id %d\n" RS, head_ptr->id);
		printf(MAR "Back from eval_token OK\n" RS);
		head_ptr = head_ptr->next;
   }
}

static void	eval_token(t_toktype *n, char **t, int *size)
{
	t_cmd_node *build_cmd = NULL;
	t_toktype	type = *n;
	char		*content = *t;
	int			i = *size;

	
	printf(OL "1 from eval_token: *size of list before | %d\n" RS, *size);
	printf(OL "1 from eval_token: token id %d\n" RS, type);
	printf(OL "1 from eval_token: token id %s\n" RS, content);
	// build_cmd = (t_cmd_node *)n;
	
	build_cmd = init_cmd(build_cmd, i);
	printf("2 from eval_token: Init build_cmd OK\n");
	i = 0;
	if (type == TOK_WORD || type == TOK_D_QUOTE || type == TOK_S_QUOTE)
	{
		// while (i < *size)
		// {
			// int	len = ft_strlen(content) + 1;
			build_cmd->cmd_args[i] = ft_strdup(content);
			printf(OR "3a hello from eval_token: build_cmd->cmd_args[i] %p\n" RS, build_cmd->cmd_args[i]);
			// if (!build_cmd->cmd_args[i])
			// 	return (0);
			// printf(GREEN "3b build_cmd->cmd_args[i] %s\n" RS, build_cmd->cmd_args[i]);
			// build_cmd->cmd_args[i][len] = '\0';
			// printf(GREEN "3c build_cmd->cmd_args[i][len] %c\n" RS, build_cmd->cmd_args[i][len]);
			i++;
			// build_cmd = init_cmd(build_cmd);
			// build_cmd_from_token_word(build_cmd, i, content);
		// }
		
		printf("3d Init cmd_word OK\n");
	}
	else if (type == TOK_REDIR_IN || type == TOK_REDIR_OUT || type == TOK_REDIR_OUT_APPEND)
	{
		// build_cmd = init_cmd(build_cmd);
		printf("4 Init cmd_word OK\n");
	}
	else if (type == TOK_ERRQUOTE)
	{
		printf("5 Error TOK_ERRQUOTE cmd_word OK\n");
	}
	while(build_cmd->cmd_args[i])
	{
		printf(YELLOW "6 build_cmd->cmd_args[i] %s\n", build_cmd->cmd_args[i]);
		i++;
	}
	// return (type);
}

// static t_token  *token_analysis_sort(t_token* head, int (*cmp)(int, int))
// {
//    t_token  *new;

//    new = head;
//    while(head->next != NULL)
//    {
//        if (((*cmp)(head->id, head->next->id)) == 0)
//        {
//            head->id = head->id ^ head->next->id;
//            head->next->id = head->id ^ head->next->id;
//            head->id = head->id ^ head->next->id;
//            head = new;
//        }
//        else
//            head = head->next;
//    }
//    head = new;
//    return (head);
// }

// int ascending(int a, int b)
// {
//  return (a <= b);
// }

void	parse(t_token *head)
{
	// t_cmd_node	*cmd;
	// t_cmd_node	*single_cmd;

	// single_cmd = NULL;
	// single_cmd = init_cmd(single_cmd);
	print_token(head);
	// if (!head)
	// 	return (NULL);
	printf("Print token OK\n");
	token_analysis(head, eval_token);
	printf("Returned from token_analysis OK\n");	
}