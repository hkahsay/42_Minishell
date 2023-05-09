#include "../../headers/minishell.h"

int	ft_count_args_cmd_word(t_token *ptr_cmd_word)
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
	// printf("arg_count: %d\n", arg_count);
	return (arg_count);
}

void	*ft_handle_word(t_ppline **new_ppline, t_token *cmd_word)
{
	int			i;
	t_token *word_ptr;

	i = 0;
	word_ptr = cmd_word;
	(*new_ppline)->ppline_cmd = (char **)my_malloc(sizeof(char *) * (ft_count_args_cmd_word(cmd_word) + 1));
	printf("(*new_ppline)->ppline_cmd %p \n", (*new_ppline)->ppline_cmd);
	if ((*new_ppline)->ppline_cmd == NULL)
	{
		my_free(new_ppline);
		return NULL;
	}
	i = 0;
	while (word_ptr != NULL && i < ft_count_args_cmd_word(cmd_word))
	{
		// printf(BLUE "word_ptr->content: %s\n" RS, word_ptr->content);
		(*new_ppline)->ppline_cmd[i] = ft_strdup(word_ptr->content);
		// printf(LBLUE "new_ppline->ppline_cmd[%d]: %s\n" RS, i, (*new_ppline)->ppline_cmd[i]);
		if ((*new_ppline)->ppline_cmd[i] == NULL)
		{
			free_ppline(new_ppline, &i);
		}
		i++;
		word_ptr = word_ptr->next;
	}
	// printf("i: %d\n", i);
	(*new_ppline)->ppline_cmd[i] = NULL;
	if (i > 0)
	{
		(*new_ppline)->pp_first_cmd = ft_strdup((*new_ppline)->ppline_cmd[0]);   //TODO : FREE
		
		// printf(ORS "i > 0 create ppline->ppline_cmd[0] %s\n", (*new_ppline)->ppline_cmd[0]);
	}
	if (i == 1)
	{
		(*new_ppline)->pp_first_cmd = ft_strdup((*new_ppline)->ppline_cmd[0]);  //TODO : FREE
		
		// printf(ORS "i == 1 create (*new_ppline)->pp_first_cmd %s\n", (*new_ppline)->pp_first_cmd);
		// break;
	}
	free_token_list(cmd_word);
	return (0);
}

