#include "../../headers/minishell.h"

static char	*mini_getenv(char *var_name, int var_len, t_envnode *mini_env)
{
	t_envnode	*temp;
	char		*empty;

	temp = mini_env;
	empty = "";
	while (temp)
	{
		if (ft_strncmp(var_name, temp->key, var_len) == 0 && \
		(int)ft_strlen(temp->key) == var_len)
			return (temp->value);
		temp = temp->next;
	}
	return (empty);
}

static char	*exp_tok_s(char **cont, char *prefix, char *exp, char *var_value)
{
	exp = ft_strjoin_free(exp, prefix);
	exp = ft_strjoin_free(exp, var_value);
	*cont = *cont + ft_strcspn(*cont + 1, " $;=+-|/\'&><\n") + 1;
	ft_strdel(&prefix);
	if (*cont == *cont - 1)
		exp = ft_strjoin_free(exp, "$");
	return (exp);
}

static char	*find_var_value(char **cont, t_envnode *mini_env,
							char *var_name, char *var_value)
{
	var_value = mini_getenv(var_name, ft_strcspn(*cont + 1, \
	" $;=+-|/\'&><\n"), mini_env);
	if (!var_value)
		var_value = "";
	ft_strdel(&var_name);
	return (var_value);
}

char	*exp_tok(char **cont, t_envnode *mini_env)
{
	char	*p;
	char	*var_name;
	char	*prefix;
	char	*exp;
	char	*var_value;

	p = *cont;
	prefix = NULL;
	exp = NULL;
	var_value = NULL;
	while (p && *p)
	{
		if (*p == '$' && p[1])
		{
			prefix = ft_substr(*cont, 0, p - *cont);
			var_name = ft_substr(p + 1, 0, ft_strcspn(p + 1, " $;=+-|/\'&><\n"));
			var_value = find_var_value(cont, mini_env, var_name, var_value);
			exp = exp_tok_s(cont, prefix, exp, var_value);
			p = *cont;
		}
		else
			p++;
	}
	return (ft_strjoin_free(exp, *cont));
}
