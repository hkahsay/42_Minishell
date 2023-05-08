#include "../../headers/minishell.h"

t_ppline	*ft_new_ppline(void) //t_cmd **cmd_ptr, 
{
	t_ppline	*new_ppline = NULL;
	new_ppline = (t_ppline *)my_malloc(sizeof(t_ppline));
	if (new_ppline == NULL)
		return NULL;
	new_ppline->pp_first_cmd = NULL;
	new_ppline->ppline_cmd = NULL;
	new_ppline->ppline_env = NULL;
	new_ppline->ppline_idx = 0;
	new_ppline->pp_pid = 0;
	new_ppline->pp_builtin_status = 0
	new_ppline->pp_red_status = 0;
	new_ppline->pp_pipe[0] = -1;
	new_ppline->pp_pipe[1] = -1;
	new_ppline->pp_infile = -1;
	new_ppline->pp_outfile = -1;
	new_ppline->heredoc = 0;
	new_ppline->hdoc_fd[0] = -1;
	new_ppline->hdoc_fd[1] = -1;
	new_ppline->exit_status = 0;
	new_ppline->next = NULL;
	printf(YELLOW "PPline after init\n" RS);
	return (new_ppline);
}

static int	ft_count_args_cmd_word(t_token *ptr_cmd_word)
{
	t_token *word_ptr;
	int arg_count;

	word_ptr = ptr_cmd_word;
	arg_count = 0;
	while (word_ptr != NULL)
	{
		arg_count++;
		word_ptr = word_ptr->next;
	}
	printf("arg_count: %d\n", arg_count);
	return (arg_count);
}

static void	*ft_handle_redir_out(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	(void)ptr_cmd_red;
	(void)new_ppline;
	printf("redir_append\n");
	return (0);
}

static void	*ft_handle_redir_append(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	(void)ptr_cmd_red;
	(void)new_ppline;
	printf("redir_out\n");
	return (0);
}

static void	*ft_handle_redir_in(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	(void)new_ppline;
	printf("redir_in\n");
	int	fd_out;

	fd_out = -1;
	if ((*ptr_cmd_red)->id == TOK_REDIR_IN)
	{
		fd_out = open((*ptr_cmd_red)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		(*new_ppline)->outfile = fd_out;
		if ((*new_ppline)->outfile < 0)
		{
			perror("open");
			exit(-1); //EXIT_FAILURE
		}
		dup2((*new_ppline)->outfile, STDOUT_FILENO);
		close((*new_ppline)->outfile);
		execve((*new_ppline)->pp_first_cmd, (*new_ppline)->ppline_cmd, (*new_ppline)->ppline_env);
		perror("execve");
		exit(-1); //EXIT_FAILURE
	}
	return (0);
}

static void	*ft_handle_heredoc(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	(void)ptr_cmd_red;
	(void)new_ppline;
	printf("heredoc\n");
	return (0);
}

static int	ft_handle_redir_all(t_ppline **new_ppline, t_token *ptr_cmd_red)
{
	printf("redir\n");
	(void)new_ppline;
	t_token *red_ptr;
	// (void)ptr_cmd_red;
	red_ptr = ptr_cmd_red;
	if (red_ptr->id == TOK_REDIR_OUT)
	{
		ft_handle_redir_out(new_ppline, &ptr_cmd_red);
		return (1);
	}
	if (red_ptr->id == TOK_REDIR_OUT_APPEND)
	{
		ft_handle_redir_append(new_ppline, &ptr_cmd_red);
		return (1);
	}
	if (red_ptr->id == TOK_REDIR_IN)
	{
		ft_handle_redir_in(new_ppline, &ptr_cmd_red);
		return (1);
	}
	if (red_ptr->id == TOK_HEREDOC)
	{
		ft_handle_heredoc(new_ppline, &ptr_cmd_red);			
		return (1);
	}
	return (0);
}

static void	free_ppline(t_ppline **new_ppline, int *i)
{
	for (int j = 0; j < *i; j++)
		my_free((*new_ppline)->ppline_cmd[j]);
	my_free((*new_ppline)->ppline_cmd);
	my_free((*new_ppline));
	// return (0);
}

static void	*ft_handle_word(t_ppline **new_ppline, t_token *cmd_word)
{
	// t_ppline	*new_ppline = NULL;
	int			i;
	t_token *word_ptr;
	// int		cmd_index = 0;
	i = 0;
	word_ptr = cmd_word;

	(*new_ppline)->ppline_cmd = (char **)my_malloc(sizeof(char *) * (ft_count_args_cmd_word(cmd_word) + 1));
	if ((*new_ppline)->ppline_cmd == NULL)
	{
		my_free(new_ppline);
		return NULL;
	}
	i = 0;
	while (word_ptr != NULL && i < ft_count_args_cmd_word(cmd_word))
	{
		printf(BLUE "word_ptr->content: %s\n" RS, word_ptr->content);
		(*new_ppline)->ppline_cmd[i] = strdup(word_ptr->content);
		printf(LBLUE "new_ppline->ppline_cmd[%d]: %s\n" RS, i, (*new_ppline)->ppline_cmd[i]);
		if ((*new_ppline)->ppline_cmd[i] == NULL)
		{
			free_ppline(new_ppline, &i);
		}
		i++;
		word_ptr = word_ptr->next;
	}
	printf("i: %d\n", i);
	(*new_ppline)->ppline_cmd[i] = NULL;
	if (i > 0)
	{
		(*new_ppline)->pp_first_cmd = strdup((*new_ppline)->ppline_cmd[0]);
		// printf(ORS "i > 0 create ppline->ppline_cmd[0] %s\n", ppline->ppline_cmd[0]);
	}
	if (i == 1)
	{
		(*new_ppline)->pp_first_cmd = strdup((*new_ppline)->ppline_cmd[0]);
		printf(ORS "i == 1 create (*new_ppline)->pp_first_cmd %s\n", (*new_ppline)->pp_first_cmd);
		// break;
	}
	return (0);
}

t_ppline	*create_ppline_array(t_cmd **cmd_head, int cmd_n, char	**mini_env_arr)
{
	// (void)cmd_n;
	t_ppline	*ppline = NULL;
	t_ppline	*new_ppline = NULL;
	t_ppline	*ppline_tail = NULL;
	t_cmd		*cmd_ptr = *cmd_head;
	t_token *word_ptr;
	// int		cmd_index = 0;
	// i = 0;
	word_ptr = cmd_ptr->cmd_word;
	// int			i;
	// // int		cmd_index = 0;
	// i = 0;
	printf(R "cmd_n: %d\n" RS, cmd_n);
	while (cmd_ptr != NULL)
	{
		new_ppline = ft_new_ppline();
		if (new_ppline == NULL)
			return NULL;
		// init_pipe(&ppline);
		new_ppline->ppline_env = mini_env_arr;
		if (cmd_ptr->cmd_word)
		{
			ft_handle_word(&new_ppline, cmd_ptr->cmd_word);
		}
		if (cmd_ptr->cmd_red)
		{
			if (ft_handle_redir_all(&new_ppline, cmd_ptr->cmd_red))
				new_ppline->red_status = 1;
		}
		if (ppline == NULL)
		{
			ppline = new_ppline;
			ppline_tail = new_ppline;
		}
		else
		{
			ppline_tail->next = new_ppline;
			ppline_tail = new_ppline;
		}
		cmd_ptr = cmd_ptr->next;
	}
	printf(YELS "CREATE PPLINE: printing ppline_list\n" RS);
	print_ppline_list(ppline, cmd_n);
	printf(RS);
	return (ppline);
}

// t_token *word_ptr = cmd_ptr->cmd_word;
	// int i = 0;
	// while (word_ptr != NULL)
	// {
	// 	new_ppline->ppline_cmd[i] = strdup(word_ptr->content);
	// 	if (new_ppline->ppline_cmd[i] == NULL)
	// 	{
	// 		// handle memory allocation error
	// 		for (int j = 0; j < i; j++)
	// 			my-free(new_ppline->ppline_cmd[j]);
	// 		my_free(new_ppline->ppline_cmd);
	// 		my-free(new_ppline);
	// 		return NULL;
	// 	}
	// 	i++;
	// 	word_ptr = word_ptr->next;
	// }

	// set the command string to the first argument

	// add the new pipeline element to the list

// char    **create_array(t_cmd **cmd_head)
// {
// 	int size;
// 	char    **array_cmd;
// 	int     i;
// 	// node = cmd_head;
// 	t_cmd *cmd_temp = *cmd_head;
// 	char	*trimmed;

// 	size = ft_list_size(cmd_temp);
// 	printf(OR "size %d\n" RS, size);

// 	array_cmd = my_malloc(sizeof(char *) * (size + 1));
// 	printf(OR "&array_cmd %p\n" RS, array_cmd);
// 	if (!array_cmd)
// 		return (0);
// 	cmd_temp = *cmd_head;
// 	i = 0;
// 	while (cmd_temp && i < size) // && !cmd_temp->cmd_wnode &&
// 	{
// 		if (cmd_temp->cmd_wnode->type == TOK_SPACE)
// 			cmd_temp->cmd_wnode = cmd_temp->cmd_wnode->next;
// 		if (cmd_temp->cmd_wnode->type == TOK_D_QUOTE)
// 		{
// 			trimmed = ft_strtrim(cmd_temp->cmd_wnode->file, "\"");
// 			free(cmd_temp->cmd_wnode->file);
// 			cmd_temp->cmd_wnode->file = ft_strdup(trimmed);
// 			printf(YELLOW "cmd_temp->cmd_wnode->file %s\n" RS, cmd_temp->cmd_wnode->file);
// 		}
// 		if (cmd_temp->cmd_wnode != NULL)

// 			array_cmd[i] = cmd_temp->cmd_wnode->file;

// 		printf("array_cmd[%d] %s\n", i, array_cmd[i]);
// 		i++;
// 		cmd_temp->cmd_wnode = cmd_temp->cmd_wnode->next;
// 	}
// 	array_cmd[i] = NULL;
// 	print_array(array_cmd);
// 	//    printf("from create array %s\n", array_cmd[i++]);
// 	return(array_cmd);

// }

// void ft_envnode_sort(t_envnode *mini_env)
// {
//     int sorted = 0; // flag to indicate if list is sorted
//     t_envnode *current;
//     // t_envnode *next;
//     t_envnode  temp;

//     while (!sorted)
//     {
//         sorted = 1; // assume the list is sorted initially
//         current = mini_env;

//         while (current && current->next)
//         {
//             if (ft_strcmp(current->key, current->next->key) > 0)
//             {
//                 // swap the key of the current and next nodes
//                 // temp = ft_strdup(current->key);
//                 // free(current->key);
//                 // current->key = ft_strdup(current->next->key);
//                 // free(current->next->key);
//                 // current->next->key = ft_strdup(temp);
//                 // free(temp);
//                 // printf("key: %s\n", current->key);
//                 // printf("value: %s\n", current->value);
//                 temp.key = ft_strdup(current->key);
//                 temp.value = ft_strdup(current->value);
//                 free(current->key);
//                 free(current->value);
//                 current->key = ft_strdup(current->next->key);
//                 current->value = ft_strdup(current->next->value);
//                 free(current->next->key);
//                 free(current->next->value);
//                 current->next->key = ft_strdup(temp.key);
//                 current->next->value = ft_strdup(temp.value);

//                 sorted = 0; // the list is not sorted yet
//             }
//             current = current->next;
//         }
//     }

//     // printf("DECLARE -X %s = %s\n", current->key, current->value);
// }
