#include "../../headers/minishell.h"

static int	ft_export_noargs(t_envnode **mini_env, t_envnode *new_env)
{
	new_env = export_no_cmd(mini_env);
	if (!new_env)
		return (-1);
	ft_envnode_sort(&new_env);
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
	t_envnode	*new_env_var;
	char		*new_content;

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
			msg_error(NULL, 0);
		ft_add_envlist(new_env_var, mini_env);
	}
	return (1);
}

static int	export_command(t_ppl **ppl, int k)
{
	// t_envnode	*new_env_var;

	// new_env_var = NULL;
	if ((*ppl)->ppl_cmd[k] && ft_strchr((*ppl)->ppl_cmd[k], '='))
	{
		if (!export_key_value(&(*ppl)->pp_list_env, \
		&(*ppl)->ppl_cmd[k]))
			return (-1);
	}
	if ((*ppl)->ppl_cmd[k] && !ft_strchr((*ppl)->ppl_cmd[k], '='))
	{
		if (!export_key(&(*ppl)->pp_list_env, &(*ppl)->ppl_cmd[k]))
			return (-1);
	}
	return (0);
}

int	ft_export(t_ppl **ppl)
{
	t_envnode	*new_env_var;
	int			k;

	new_env_var = NULL;
	k = 0;
	if ((*ppl)->ppl_cmd[1] == NULL && (*ppl)->pp_list_env)
	{
		if (!ft_export_noargs(&(*ppl)->pp_list_env, new_env_var))
			return (-1);
		return (EXIT_SUCCESS);
	}
	while ((*ppl)->ppl_cmd[++k])
	{
		if (export_command(ppl, k) == -1)
			return (-1);
	}
	return (EXIT_SUCCESS);
}

// int	ft_export(t_ppl **ppl)
// {
// 	t_envnode	*new_env_var;
// 	int			k;

// 	new_env_var = NULL;
// 	k = 0;
// 	if ((*ppl)->ppl_cmd[1] == NULL && (*ppl)->pp_list_env)
// 	{
// 		if (!ft_export_noargs(&(*ppl)->pp_list_env, new_env_var))
// 			return (-1);
// 		return (EXIT_SUCCESS);
// 	}
// 	while ((*ppl)->ppl_cmd[++k])
// 	{
// 		if ((*ppl)->ppl_cmd[k]
// 			&& ft_strchr((*ppl)->ppl_cmd[k], '='))
// 		{
// 			if (!export_key_value(&(*ppl)->pp_list_env,
// 					&(*ppl)->ppl_cmd[k]))
// 				return (-1);
// 		}
// 		if ((*ppl)->ppl_cmd[k]
// 			&& !ft_strchr((*ppl)->ppl_cmd[k], '='))
// 		{
// 			if (!export_key(&(*ppl)->pp_list_env, &(*ppl)->ppl_cmd[k]))
// 				return (-1);
// 		}
// 		// ft_export_args()
// 	}
// 	return (EXIT_SUCCESS);
// }
