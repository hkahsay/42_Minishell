#include "../../headers/minishell.h"

static char	*mini_getenv(char *var_name, int var_len, t_envnode *mini_env)
{
	t_envnode	*temp;
	char		*empty;

	temp = mini_env;
	empty = "";
	while(temp)
	{
		if (ft_strncmp(var_name, temp->key, var_len) == 0  && (int)ft_strlen(temp->key) == var_len)
			return (temp->value);
		temp = temp->next;
	}
	return (empty);
}

char	*expand_token(char **content, t_envnode *mini_env)
{
	char	*p;
	int		var_len;
	char	*var_name;
	char	*var_value;
	char	*prefix;
	char	*expanded_content;

	p = *content;
	prefix = NULL;
	expanded_content = NULL;
	while (p && *p)
	{
		if (*p == '$' && p[1])
		{
			prefix = ft_substr(*content, 0, p - *content);
			printf(LB "EXPAND: prefix %s\n" RS, prefix);
			var_len = ft_strcspn(p + 1, " $;|&><\n");
			var_name = ft_substr(p + 1, 0, var_len);
			printf(LB "EXPAND: var_name %s\n" RS, var_name);
			var_value = mini_getenv(var_name, var_len, mini_env);
			printf(LB "EXPAND: var_value %s\n" RS, var_value);
			if (!var_value)
				var_value = "";
			ft_strdel(&var_name);
			expanded_content = ft_strjoin_free(expanded_content, prefix);
			printf(LB "EXPAND: expanded_content %s\n" RS, expanded_content);
			expanded_content = ft_strjoin_free(expanded_content, var_value);
			printf(LB "EXPAND: expanded_content %s\n" RS, expanded_content);
			*content = p + var_len + 1;
			printf(LB "EXPAND: *content %s\n" RS, *content);
			ft_strdel(&prefix);
			if (*content == p + 1)
			{
				expanded_content = ft_strjoin_free(expanded_content, "$");
				printf(LB "EXPAND: expanded_content %s\n" RS, expanded_content);
			}
			p = *content;
			printf(LB "EXPAND: p %s\n" RS, p);
		}
		else
			p++;
	}
	return (ft_strjoin_free(expanded_content, *content));
}

void    *expand_token_list(t_token **token_head, t_envnode *mini_env)
{
	t_token	*curr;
	char	*exp_content;
	char	*d_trimmed;
	char	*s_trimmed;

	curr = *token_head;
	// d_quote = "\"";
	// s_quote = "\'";
	while (curr != NULL)
	{
		if (curr->id == TOK_WORD || curr->id == TOK_D_QUOTE)
		{
			if (curr->id == TOK_D_QUOTE)
			{
				d_trimmed = ft_strtrim(curr->content, "\""); //d_quote
				my_free(curr->content);
				curr->content = d_trimmed;
				curr->id = TOK_D_QUOTE;
			}
			// printf(LB "EXPAND_TOKEN_LIST: curr->content %s\n" RS, curr->content);
			if (ft_strncmp(curr->content, "$?", 2) != 0)
			{
				exp_content = expand_token(&curr->content, mini_env);
				curr->content = ft_strdup(exp_content);
			}
			// if (ft_strncmp(curr->content, "$?", 2) == 0)
			// 	exp_content = curr->content;
			// printf(LB "EXPAND_TOKEN_LIST: curr->content %s\n" RS, curr->content);
			if (exp_content == NULL)
				return (NULL);
		}
		if (curr->id == TOK_S_QUOTE)
		{
			s_trimmed = ft_strtrim(curr->content, "\'"); //s_quote
			my_free(curr->content);
			curr->content = s_trimmed;
			curr->id = TOK_S_QUOTE;
		}
		curr = curr->next;
	}
	return (*token_head);
}
