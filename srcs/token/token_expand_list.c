#include "../../headers/minishell.h"

static void	*exp_toklist_s(t_token *curr, t_envnode *mini_env, \
char *exp, char *d_trim)
{
	if (curr->id == T_DQ)
	{
		d_trim = ft_strtrim(curr->content, "\"");
		my_free(curr->content);
		curr->content = d_trim;
		curr->id = T_DQ;
	}
	if (ft_strncmp(curr->content, "$?", 2) != 0)
	{
		exp = exp_tok(&curr->content, mini_env);
		if (exp == NULL)
			return (NULL);
		my_free(curr->content);
		curr->content = ft_strdup(exp);
		my_free(exp);
	}
	if (ft_strncmp(curr->content, "$?", 2) != 0 && exp == NULL)
		return (NULL);
	return (curr);
}

void	*exp_toklist(t_token **token_head, t_envnode *mini_env)
{
	t_token	*curr;
	char	*exp;
	char	*d_trim;
	char	*s_trim;

	curr = *token_head;
	exp = NULL;
	d_trim = NULL;
	s_trim = NULL;
	while (curr != NULL)
	{
		if (curr->id == T_W || curr->id == T_DQ)
			curr = exp_toklist_s(curr, mini_env, exp, d_trim);
		if (curr->id == T_SQ)
		{
			s_trim = ft_strtrim(curr->content, "\'");
			my_free(curr->content);
			curr->content = ft_strdup(s_trim);
			my_free(s_trim);
			curr->id = T_W;
		}
		curr = curr->next;
	}
	return (*token_head);
}
