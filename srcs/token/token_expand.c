#include "../../headers/minishell.h"

static char	*mini_getenv(char *var_name, int var_len, t_envnode *mini_env)
{
	t_envnode	*temp;
	char		*empty;

	temp = mini_env;
	empty = "";
	while(temp)
	{
		if (ft_strncmp(var_name, temp->key, var_len) == 0  && (int)ft_strlen(temp->key) == var_len) // && var_name == temp->key
		{
			printf(GREEN "FOUND var_name: %s\n temp->key: %s\n temp->value: %s\n" RS, var_name, temp->key, temp->value);
			return (temp->value);
		}
		temp = temp->next;
	}
	printf("no value found!\n");
	return (empty); //return ("");
}

char	*expand_token(char **content, t_envnode *mini_env)
{
	printf(R "expand_token function *content: %s\n" RS, *content);
	char *p;
	int		var_len;
	char	*var_name;
	char	*var_value;
	char	*prefix = NULL;
	char	*suffix = NULL;
	char	*expanded_content = NULL;

	p = *content;
	// char *s = NULL;
	// char *r = NULL;
	printf("begin expand p: %s\n", p);
		while (p && *p)
		{
			if (*p == '$' && p[1])
		{
			prefix = ft_substr(*content, 0, p - *content);
			suffix = ft_strdup(p + 1);
			// if (ft_strncmp(suffix, "?", 1) == 0)
			// {
			// 	var_value = ft_itoa(g_mini.status);
			// 	var_len = 1;
			// }
			// else
			// {
			var_len = ft_strcspn(p + 1, " $;|&><\n");
			var_name = ft_substr(p + 1, 0, var_len);
			var_value = mini_getenv(var_name, var_len, mini_env);
			if (!var_value)
			{
				var_value = "";
				//TOK_EMPTY
			}
			ft_strdel(&var_name);
			// }
			expanded_content = ft_strjoin_free(expanded_content, prefix);
			expanded_content = ft_strjoin_free(expanded_content, var_value);
			*content = p + var_len + 1;
			ft_strdel(&prefix);
			ft_strdel(&suffix);
			
			if (*content == p + 1)
				expanded_content = ft_strjoin_free(expanded_content, "$");
			p = *content;
		}
		else
			p++;

			// p = s;
	}
	// printf("expand end p: %s\n", p);
	expanded_content = ft_strjoin_free(expanded_content, *content);
	return (expanded_content);
}

void    *expand_token_list(t_token **token_head, t_envnode *mini_env)
{
	// t_token *new_exp_token = NULL;
	// t_token *exp_token_head;
	// t_token	*exp_token_tail;
	t_token	*curr;
	char	*exp_content;
	char	*d_trimmed;
	char	*s_trimmed;
	char		*d_quote = "\"";
	char		*s_quote = "\'";

	// exp_token_head = token_head;
	// exp_token_tail = NULL;

	curr = *token_head;
	// init_token(new_exp_token);
	// printf(GREEN "expand_token_list 1\n" RS);
	while (curr != NULL)
	{
		printf("1\n");
		printf(GREEN "expand_token_list 2\n" RS);
		printf(MAR "TOKEN: %s=%d\n" RS, curr->content, curr->id);
		if (curr->id == TOK_WORD || curr->id == TOK_D_QUOTE)
		{
			if (curr->id == TOK_D_QUOTE)
			{
				d_trimmed = ft_strtrim(curr->content, d_quote);
				// curr->content = ft_strdup(d_trimmed);
				free(curr->content);
				curr->content = d_trimmed;
				curr->id = TOK_D_QUOTE;
				printf(OR "curr->content %s\n" RS, curr->content);
			}
			printf(GREEN "expand_token_list 3\n" RS);
			exp_content = expand_token(&curr->content, mini_env); //, curr->id
			printf(R "RETURNED to exp_token_list content: %s => %s\n" RS, curr->content, exp_content);
			// curr->content = ft_strdup(exp_content);
			// free(curr->content);
			curr->content = ft_strdup(exp_content);
			// curr->content = exp_content;
			printf(OR "curr->content %s\n" RS, curr->content);
			if (exp_content == NULL)
				return (NULL);
		}
		if (curr->id == TOK_S_QUOTE)
		{
			s_trimmed = ft_strtrim(curr->content, s_quote);
			// free(curr->content);
			// curr->content = ft_strdup(s_trimmed);
			free(curr->content);
			curr->content = s_trimmed;
			curr->id = TOK_S_QUOTE;
			printf(OR "curr->content %s\n" RS, curr->content);
		}
		curr = curr->next;
	}
	print_token(*token_head);
	return (*token_head);
}
