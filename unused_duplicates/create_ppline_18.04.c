#include "../../headers/minishell.h"

// int ft_cmd_size(t_cmd *node)
// {
//     t_wr_node *args = node->cmd_wnode;
//     int size = 0;
//     while (args != NULL) {
//         if (args->file != NULL)
//             size++;
//         args= args->next;
//     }
//     return size;
// }

//

// char	**mini_env_to_array(t_envnode	*mini_env)
// {
// 	char	**mini_env_array;


// }
t_ppline	*ft_new_ppline(char **mini_env_arr) //t_cmd **cmd_ptr, 
{
	t_ppline	*new_ppline = NULL;
	new_ppline = (t_ppline *)malloc(sizeof(t_ppline));
	if (new_ppline == NULL)
	{
		// handle memory allocation error
		return NULL;
	}

	// new_mini = init_mini();
	// initialize the new pipeline element
	new_ppline->pp_first_cmd = NULL;
	// new_ppline->pp_first_cmd_path = NULL;
	new_ppline->ppline_cmd = NULL;
	new_ppline->ppline_env = mini_env_arr;
	// new_ppline->ppline_idx = cmd_index;
	new_ppline->infile = -1;
	new_ppline->outfile = -1;
	new_ppline->heredoc = 0;
	new_ppline->hdoc_fd[0] = -1;
	new_ppline->hdoc_fd[1] = -1;
	new_ppline->exit_status = 0;
	new_ppline->next = NULL;
	printf(YELLOW "PPline after init\n" RS);
	// print_one_ppline(new_ppline);
	return (new_ppline);
}

int	ft_count_args_cmd_word(t_token *ptr_cmd_word)
{
	t_token *word_ptr = ptr_cmd_word;
	int arg_count = 0;
	while (word_ptr != NULL)
	{
		arg_count++;
		word_ptr = word_ptr->next;
	}
	return (arg_count);
}

t_ppline	*create_ppline_array(t_cmd **cmd_head, int cmd_n, char	**mini_env_arr)
{
	(void)cmd_n;
	t_ppline	*ppline = NULL;
	t_ppline	*new_ppline = NULL;
	t_ppline	*ppline_tail = NULL;
	t_cmd	*cmd_ptr = *cmd_head;
	// int		cmd_index = 0;

	while (cmd_ptr != NULL)
	{
		new_ppline = ft_new_ppline(mini_env_arr); //cmd_ptr, 
		// new_ppline = (t_ppline *)malloc(sizeof(t_ppline));
		// if (new_ppline == NULL)
		// {
		// 	// handle memory allocation error
		// 	return NULL;
		// }

		// // new_mini = init_mini();
		// // initialize the new pipeline element
		// new_ppline->pp_first_cmd = NULL;
		// new_ppline->pp_first_cmd_path = NULL;
		// new_ppline->ppline_cmd = NULL;
		// new_ppline->ppline_env = mini_env_arr;
		// new_ppline->ppline_idx = cmd_index;
		// new_ppline->infile = -1;
		// new_ppline->outfile = -1;
		// new_ppline->heredoc = 0;
		// new_ppline->hdoc_fd[0] = -1;
		// new_ppline->hdoc_fd[1] = -1;
		// new_ppline->exit_status = 0;
		// new_ppline->next = NULL;
		if (cmd_ptr->cmd_word)
		{
			new_ppline->ppline_cmd = (char **)malloc(sizeof(char *) * (ft_count_args_cmd_word(cmd_ptr->cmd_word) + 1));
			// ft_count_args_cmd_word(cmd_ptr->cmd_word);
		}
		// count the number of arguments in a command
		// t_token *word_ptr = cmd_ptr->cmd_word;
		// int arg_count = 0;
		// while (word_ptr != NULL)
		// {
		// 	arg_count++;
		// 	word_ptr = word_ptr->next;
		// }

		if (new_ppline->ppline_cmd == NULL)
		{
			// handle memory allocation error
			free(new_ppline);
			return NULL;
		}

		t_token *word_ptr = cmd_ptr->cmd_word;
		int i = 0;
		while (word_ptr != NULL)
		{
			new_ppline->ppline_cmd[i] = strdup(word_ptr->content);
			if (new_ppline->ppline_cmd[i] == NULL)
			{
				// handle memory allocation error
				for (int j = 0; j < i; j++)
					free(new_ppline->ppline_cmd[j]);
				free(new_ppline->ppline_cmd);
				free(new_ppline);
				return NULL;
			}
			i++;
			word_ptr = word_ptr->next;
		}
		new_ppline->ppline_cmd[i] = NULL;

		// set the command string to the first argument
		if (i > 0)
			new_ppline->pp_first_cmd = strdup(new_ppline->ppline_cmd[0]);

		// add the new pipeline element to the list
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

		// move to the next command in the pipeline
		cmd_ptr = cmd_ptr->next;
		cmd_n++;
	}
	printf(YELS "EXECUTE: printing cmd_list\n " RS);
	print_ppline_list(ppline);
	printf(RS);
	return (ppline);
}



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

// 	array_cmd = malloc(sizeof(char *) * (size + 1));
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
