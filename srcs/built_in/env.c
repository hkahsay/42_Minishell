#include"../../headers/minishell.h"

int ft_env(char **args, t_envnode **mini_env)
{
    (void)args;
    t_envnode *mini_envp = *mini_env;
    // int     i = 0;

    // mini_envp->content = malloc(strlen(mini_envp->key) + strlen(mini_envp->value) + 2); // +2 for the '=' sign and null terminator
    if(!mini_envp)
        return(0);
    // mini_envp = ft_join_env(&mini_envp);
    // *mini_env = mini_envp;
    // printf("mini_envp->content2%s\n", (*mini_env)->content);
    // while (mini_envp->next)
    // {
    //     // while (mini_envp->content)
    //     // {
    //     //    if(mini_envp->content[i] == '=' )
    //     //     {
    //             printf("%s\n", mini_envp->content);
    //         //     i++;

    //         // }
        
    //     // if (ft_strcmp(mini_envp->content, "=") == 0)
    //     mini_envp = mini_envp->next;
    // }
    print_mini_envp(mini_envp);
    return(0);  
}
	
	
	
// 	int ft_env(char **args, t_envnode **mini_env)
// 	{
// 		(void)args;
// 		int     i = 0;
// 		t_envnode *mini_envp = *mini_env;

// 		if(!mini_envp)
// 			return(0);
// 		while ((mini_envp)) //->key && (mini_envp)->value
// 		{
// 			if ((mini_envp)->value) // == '='
// 			{
// 				printf("ENV: %s=%s\n", mini_envp->key, mini_envp->value);
// 				// print_mini_envp((mini_envp));
// 				i++;
// 				// break;
// 			}
			
// 			(mini_envp) = (mini_envp)->next;
// 		}
// 		printf("env num %d\n", i);
// 		printf("env is ok\n");
// 		return(0);
// 	}

// // int ft_env(char **args, t_envnode **env_var)
// // {
// //     (void)args;
// //     (void)env_var;
// //     printf("ft_env\n");
// //     return 0;
// // }
