#include "../../headers/minishell.h"

static int	ft_export_noargs(t_envnode **mini_env, t_envnode *new_env)
{
	new_env = export_no_cmd(mini_env);
	if (!new_env)
	{
		// printf(YELLOW"new_env\n"RS);
		return (-1);
	}
	// printf("content beginning: %s\n", (new_env)->content);
	ft_envnode_sort(&new_env);
	// printf(YELLOW"only expo\n"RS);
	print_ex_sorted_envp(new_env);
	return (1);
}

static int	export_key_value(t_envnode **mini_env, char **cmd_args)
{
	char	*new_key;
	char	*new_value;
	int		i;
	int		j;
	char	*new_content;

	i = 0;
	new_content = *cmd_args;
	while (new_content[i] != '=')
		i++;
	new_key = ft_substr(new_content, 0, i);
	i++;
	j = 0;
	while (new_content[j] != '\0')
		j++;
	new_value = ft_substr(new_content, i, j);
	if (!ft_setenv(new_key, new_value, new_content, mini_env))
		return (-1);
	return (1);
}

static int	export_key(t_envnode **mini_env, char **cmd_args)
{
	char		*new_key;
	char		*new_value;
	// int			i;
	t_envnode	*new_env_var;
	char		*new_content;

	// i = 0;
	new_env_var = NULL;
	new_content = *cmd_args;
	new_key = ft_strdup(new_content);
	new_env_var = find_env_var(new_key, mini_env);
	if (new_env_var)
		return (1);
	else
	{
		new_value = "";
		new_env_var = create_mini_envvar_node(new_key, new_value, new_key);
		if (!new_env_var)
			msg_error(NULL, 0);//to be checked
		ft_add_envlist(new_env_var, mini_env);
	}
	return (1);
}

int	ft_export(t_ppline **ppline)
{
	t_envnode	*new_env_var;
	int			k;
	// t_envnode *cur_env_var;
	new_env_var = NULL;
	// cur_env_var = (*ppline)->pp_list_env;
	k = 0;
	if ((*ppline)->ppline_cmd[1] == NULL && (*ppline)->pp_list_env)
	{
		if (!ft_export_noargs(&(*ppline)->pp_list_env, new_env_var))
			return (-1);
		return (EXIT_SUCCESS);
	}
	while ((*ppline)->ppline_cmd[++k])
	{
		if ((*ppline)->ppline_cmd[k]
			&& ft_strchr((*ppline)->ppline_cmd[k], '='))
		{
			if (!export_key_value(&(*ppline)->pp_list_env,
					&(*ppline)->ppline_cmd[k]))
				return (-1);
		}
		if ((*ppline)->ppline_cmd[k]
			&& !ft_strchr((*ppline)->ppline_cmd[k], '='))
		{
			if (!export_key(&(*ppline)->pp_list_env, &(*ppline)->ppline_cmd[k]))
				return (-1);
		}
	}
	return (EXIT_SUCCESS);
}
