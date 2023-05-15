#include "../../headers/minishell.h"

int	count_args_cmd_word(t_token *ptr_cmd_word)
{
	t_token	*word_ptr;
	int		arg_count;

	word_ptr = ptr_cmd_word;
	arg_count = 0;
	while (word_ptr != NULL)
	{
		arg_count++;
		word_ptr = word_ptr->next;
	}
	return (arg_count);
}

static void	fill_word_array_loop(t_ppl **new_ppl, t_token *cmd_word, int *i)
{
	t_token	*word_ptr;

	word_ptr = cmd_word;
	while (word_ptr != NULL && *i < count_args_cmd_word(cmd_word))
	{
		(*new_ppl)->ppl_cmd[*i] = ft_strdup(word_ptr->content);
		if ((*new_ppl)->ppl_cmd[*i] == NULL)
		{
			free_ppl(new_ppl, i);
			return ;
		}
		(*i)++;
		word_ptr = word_ptr->next;
	}
	(*new_ppl)->ppl_cmd[*i] = NULL;
}

static void	fill_word_array(t_ppl **new_ppl, t_token *cmd_word)
{
	int	i;

	i = 0;
	(*new_ppl)->ppl_cmd = (char **)my_malloc(sizeof(char *) * \
	(count_args_cmd_word(cmd_word) + 1));
	if ((*new_ppl)->ppl_cmd == NULL)
	{
		my_free(new_ppl);
		return ;
	}
	fill_word_array_loop(new_ppl, cmd_word, &i);
	if (i > 0)
		(*new_ppl)->pp_first_cmd = ft_strdup((*new_ppl)->ppl_cmd[0]);
	else if (i == 1)
		(*new_ppl)->pp_first_cmd = ft_strdup((*new_ppl)->ppl_cmd[0]);
	free_token_list(cmd_word);
}

void	*handle_word(t_ppl **new_ppl, t_token *cmd_word)
{
	fill_word_array(new_ppl, cmd_word);
	return (NULL);
}
