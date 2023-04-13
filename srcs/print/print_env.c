#include"../../headers/minishell.h"

void print_mini_envp(t_envnode *temp)
{
	int i = 0;

	while (temp)
	
	{
		// if (temp->next && (!temp->value || temp->value[0] == '\0'))
		
		// {
		// 	temp = temp->next;
		// }
		// else
		// if (temp->next && !ft_strchr(temp->content, '='))
		// {
		// 	printf(OR "%s\n" RS, temp->content);
		// 	temp = temp->next;
		// }
		if (ft_strchr(temp->content, '='))
			printf("%s=%s\n", temp->key, temp->value);
		i++;
		temp = temp->next;
	}
	printf("%d\n", i);
}

void print_ex_sorted_envp(t_envnode *mini_env, char **cmd_arg)
{
	printf("SORTED\n");
	int i = 0;
	(void)cmd_arg;

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

// void ft_join_env2(t_envnode **mini_env)
// {
//     t_envnode *mini_envp = *mini_env;
//     // int     i = 0;
//     while (mini_envp)
//     {
//         mini_envp->content = malloc(ft_strlen(mini_envp->key) + ft_strlen(mini_envp->value) + 2); // +2 for the '=' sign and null terminator
//         if (mini_envp->content == NULL)
//         {
//             // Handle error
//             return;
//         }

//         strcpy(mini_envp->content, mini_envp->key); // Copy mini_envp->key to mini_envp->content
//         strcat(mini_envp->content, "="); // Append '=' to mini_envp->content
//         strcat(mini_envp->content, mini_envp->value);
//         // printf("mini_envp->content%s\n", mini_envp->content);
//         (*mini_env) = (*mini_env)->next;
//         mini_envp = *mini_env;
//         // mini_envp = mini_envp->next;
//     }
//     // return (mini_envp);
//     // while (mini_envp)
//     // {
//     //     /* code */
//     // }
    
// }

// void print_ex_envp(t_envnode *mini_env, char **cmd_arg)
// {
// 	int i = 0;
// 	(void)cmd_arg;

// 	while (mini_env)
// 	{
// 		if (!mini_env->value)
// 		{
// 			printf("declare -x %s\n", mini_env->content);
// 		}
// 		else
// 			printf("declare -x %s\n", mini_env->content);
// 		i++;
// 		mini_env = mini_env->next;
// 	}
// 	printf("%d\n", i);
// }



// void print_ex_sorted_no_egal_envp(t_envnode *mini_env, char **cmd_arg)
// {
// 	printf("SORTED\n");
// 	int i = 0;
// 	(void)cmd_arg;

// 	while (mini_env)
// 	{
// 		if (!mini_env->value || mini_env->value[0] == '\0')
// 		{
// 			printf("declare -x %s\n", mini_env->content);
// 		}
// 		else
// 			printf("declare -x %s=\"%s\"\n", mini_env->key, mini_env->value);
// 		i++;
// 		mini_env = mini_env->next;
// 	}
// 	printf("%d\n", i);
// }
// void print_ex_no_value(t_envnode *mini_env)
// {
//     while (mini_env)
//     {
//         if (mini_env->value == NULL) //mini_env->value && 
//         {
//             printf("%s", mini_env->key);
//             printf("\n");
//         }
// 		if (mini_env->value)
// 			printf("%s%s\n", mini_env->key, mini_env->value);
//         mini_env = mini_env->next;
//     }
// }