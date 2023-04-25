#include"../../headers/minishell.h"

// while ((*ppline)->ppline_cmd[i])
	// {
	// 	ft_putstr_fd((*ppline)->ppline_cmd[i], STDOUT_FILENO);
	// 	if ((*ppline)->ppline_cmd[i + 1])
	// 		ft_putchar_fd(' ', STDOUT_FILENO);
	// 	i++;
	// }
	// if ((*ppline)->ppline_cmd[1] && ft_strcmp((*ppline)->ppline_cmd[1], "-n") != 0)
	// 	ft_putchar_fd('\n', STDOUT_FILENO);
	// printf("ft_echo\n");

int	find_flag(char *cmd)//t_ppline **ppline
{
	int	i;
	// int	j;

	i = 0;
	// while (cmd)
	// {
		if (!cmd)
			return (-1);
		if (ft_strncmp(&cmd[i], "-", 1) == 0 && ft_strncmp(&cmd[i + 1], "n", 1) == 0)
		{
			i = i + 2;
			while (cmd[i])
			{
				if (ft_strncmp(&cmd[i], "n", 1) != 0)
					return (-1);
				else
					i++;	
			}
			return(0);
		}
	// 	// i++;
	// }
	return(-1);
	
}

int ft_echo(t_ppline **ppline) //char **args, t_envnode **env_var
{
	int i;
	int	flag_n;
	int	flag_echo;
	int	exit_status;
	// (void)env_var;
	i = 1;
	flag_n = 0;
	flag_echo = 0;
	exit_status = 0;

	printf("1\n");
	if (!(*ppline)->ppline_cmd)
		return(-1);
	if (!(*ppline)->ppline_cmd[1])
	{
		flag_echo = 1;	
		exit_status = print_and_return(ppline, flag_echo, flag_n);
		return (exit_status);
	}
	if (find_flag((*ppline)->ppline_cmd[1]) == 0)
		flag_n = 1;
	printf("flag_n: %d\n", flag_n);	
	exit_status = print_and_return(ppline, flag_echo, flag_n);
	printf(R "ECHO exit_status: %d\n" RS, exit_status);	
	return (exit_status);
}

int	print_and_return(t_ppline **ppline, int flag_echo, int flag_n)
{
	int	i;

	i = 0;
	// while ((*ppline)->ppline_cmd[i])
	// {
		if (flag_echo == 1)
		{
			printf("flag_n: %d\n", flag_n);	
			// g_exit_status = 0;
			write(1, "\n", 1);
			return (EXIT_SUCCESS); //g_exit_status
		}
		if (flag_n == 1)
		{
			if (!(*ppline)->ppline_cmd[i + 2])
			{
				// g_exit_status = 0;
				return (EXIT_SUCCESS); //g_exit_status
			}
			else
			{
				i = i + 2;
				// ft_putstr_fd((*ppline)->ppline_cmd[i + 2], STDOUT_FILENO);
				// if ((*ppline)->ppline_cmd[i + 1])
				// 	ft_putchar_fd(' ', STDOUT_FILENO);
				while ((*ppline)->ppline_cmd[i])
				{
					// while ()
					ft_putstr_fd((*ppline)->ppline_cmd[i], STDOUT_FILENO);
					if ((*ppline)->ppline_cmd[i + 1])
						ft_putchar_fd(' ', STDOUT_FILENO);
					i++;
				}
			}
		}
		else
		{
			i = 1;
			while ((*ppline)->ppline_cmd[i])
			{
				ft_putstr_fd((*ppline)->ppline_cmd[i], STDOUT_FILENO);
				if ((*ppline)->ppline_cmd[i + 1])
					ft_putchar_fd(' ', STDOUT_FILENO);
				i++;
			}
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
	return (EXIT_SUCCESS); //g_exit_status
}

