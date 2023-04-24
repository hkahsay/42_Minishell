#include"../../headers/minishell.h"

void print_mini_envp(t_envnode *temp)
{
	int i = 0;

	while (temp)	
	{
		if (ft_strchr(temp->content, '='))
		{
			printf("%s=%s\n", temp->key, temp->value);
			i++;
		}
		temp = temp->next;
	}
	printf("%d\n", i);
}

void print_ex_sorted_envp(t_envnode *mini_env) //, char **cmd_arg
{
	printf("SORTED\n");
	int i = 0;
	// (void)cmd_arg;

	while (mini_env)
	{
		if (ft_strchr(mini_env->content, '=') && (!mini_env->value || mini_env->value[0] == '\0'))
			printf("declare -x %s\"\"\n", mini_env->content);
		else if (!ft_strchr(mini_env->content, '=') && (!mini_env->value || mini_env->value[0] == '\0'))
		{
			printf("declare -x %s\n", mini_env->content);
		}
		else
			printf("declare -x %s=\"%s\"\n", mini_env->key, mini_env->value);
		i++;
		mini_env = mini_env->next;
	}
	printf("%d\n", i);
}

void	print_mini_env_array(char **mini_env_array)
{
	int	i;

	i = 0;
	while (mini_env_array[i])
	{
		printf(PURPLE "mini_env_array %s\n", mini_env_array[i++]);
	}
	printf("%d\n" RS, i);
}
