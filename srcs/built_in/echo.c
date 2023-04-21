#include"../../headers/minishell.h"

int ft_echo(char **args, t_envnode **env_var)
{
	int i;
	(void)env_var;
	i = 1;

	// close(STDOUT_FILENO);
	// dup2((ppline)->pp_outfile, STDOUT_FILENO);
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (args[1] && ft_strcmp(args[1], "-n") != 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	// printf("ft_echo\n");
	return 0;
}

// void	ft_putchar_fd(char c)
// {
// 	write(1, &c, 1);
// }

// int	ft_putstr(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		ft_putchar(str[i]);
// 		i++;
// 	}
// 	return(i);
// }
