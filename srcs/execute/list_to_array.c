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

t_pmd	*create_array(t_cmd **cmd_head, int cmd_n)
{
	// t_pmd	**pmd;
	// int		i;

	// i = 0;
	// pmd = init_pmd(void);
	// while (cmd_head[i] && i < cmd_n)
	// {
	// 	pmd[i] =
	// }
// t_pmd	*create_pmd(t_cmd *cmd_list)
// {
	(void)cmd_n;
	t_pmd	*pmd = NULL;
	t_pmd	*new_pmd = NULL;
	t_pmd	*pmd_tail = NULL;
	t_cmd	*cmd_ptr = *cmd_head;
	int		cmd_index = 0;

	while (cmd_ptr != NULL)
	{
		// allocate memory for the new pipeline element
		new_pmd = (t_pmd *)malloc(sizeof(t_pmd));
		if (new_pmd == NULL)
		{
			// handle memory allocation error
			return NULL;
		}

		// initialize the new pipeline element
		new_pmd->cmd = NULL;
		new_pmd->pmd_cmd = NULL;
		new_pmd->pmd_index = cmd_index;
		new_pmd->infile = -1;
		new_pmd->heredoc = 0;
		new_pmd->hdoc_fd[0] = -1;
		new_pmd->hdoc_fd[1] = -1;
		new_pmd->next = NULL;

		// count the number of arguments in a command
		t_token *word_ptr = cmd_ptr->cmd_word;
		int arg_count = 0;
		while (word_ptr != NULL)
		{
			arg_count++;
			word_ptr = word_ptr->next;
		}

		new_pmd->pmd_cmd = (char **)malloc(sizeof(char *) * (arg_count + 1));
		if (new_pmd->pmd_cmd == NULL)
		{
			// handle memory allocation error
			free(new_pmd);
			return NULL;
		}

		word_ptr = cmd_ptr->cmd_word;
		int i = 0;
		while (word_ptr != NULL)
		{
			new_pmd->pmd_cmd[i] = strdup(word_ptr->content);
			if (new_pmd->pmd_cmd[i] == NULL)
			{
				// handle memory allocation error
				for (int j = 0; j < i; j++)
					free(new_pmd->pmd_cmd[j]);
				free(new_pmd->pmd_cmd);
				free(new_pmd);
				return NULL;
			}
			i++;
			word_ptr = word_ptr->next;
		}
		new_pmd->pmd_cmd[i] = NULL;

		// set the command string to the first argument
		if (i > 0)
			new_pmd->cmd = strdup(new_pmd->pmd_cmd[0]);

		// add the new pipeline element to the list
		if (pmd == NULL)
		{
			pmd = new_pmd;
			pmd_tail = new_pmd;
		}
		else
		{
			pmd_tail->next = new_pmd;
			pmd_tail = new_pmd;
		}

		// move to the next command in the pipeline
		cmd_ptr = cmd_ptr->next;
		cmd_n++;
	}
	print_pmd_list(pmd);
	return pmd;
}

void print_pmd_list(t_pmd *pmd_list)
{
    t_pmd *current = pmd_list;
    while (current != NULL) {
        printf("Command: %s\n", current->cmd);
        printf("Command arguments:\n");
        for (int i = 0; current->pmd_cmd[i] != NULL; i++) {
            printf("%s\n", current->pmd_cmd[i]);
        }
        printf("Redirections:\n");
        printf("Input file: %d\n", current->infile);
        printf("Heredoc: %d\n", current->heredoc);
        printf("Heredoc FDs: %d %d\n", current->hdoc_fd[0], current->hdoc_fd[1]);
        printf("\n");

        current = current->next;
    }
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
