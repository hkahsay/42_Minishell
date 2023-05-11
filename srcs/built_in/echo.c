#include"../../headers/minishell.h"

int	find_flag(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (-1);
	if (ft_strncmp(&cmd[i], "-", 1) == 0 \
	&& ft_strncmp(&cmd[i + 1], "n", 1) == 0)
	{
		i = i + 2;
		while (cmd[i])
		{
			if (ft_strncmp(&cmd[i], "n", 1) != 0)
				return (-1);
			else
				i++;
		}
		return (0);
	}
	return (-1);
}

int	ft_echo(t_ppline **ppline)
{
	int	flag_n;
	int	flag_echo;

	flag_n = 0;
	flag_echo = 0;
	if (!(*ppline)->ppline_cmd)
		return (EXIT_FAILURE);
	if (!(*ppline)->ppline_cmd[1])
	{
		flag_echo = 1;
		(*ppline)->pp_exit = print_and_return(ppline, flag_echo, flag_n);
		my_free((*ppline)->pp_first_cmd);
		my_free((*ppline)->ppline_cmd[0]);
		my_free((*ppline)->ppline_cmd[1]);
		return (EXIT_SUCCESS);
	}
	if (find_flag((*ppline)->ppline_cmd[1]) == 0)
		flag_n = 1;
	(*ppline)->pp_exit = print_and_return(ppline, flag_echo, flag_n);
	my_free((*ppline)->pp_first_cmd);
	my_free((*ppline)->ppline_cmd[0]);
	my_free((*ppline)->ppline_cmd[1]);
	return (EXIT_SUCCESS);
}

static void	print_echo_n_flag(t_ppline *ppline, int i)
{
	while (ppline->ppline_cmd[i])
	{
		ft_putstr_fd(ppline->ppline_cmd[i], STDOUT_FILENO);
		if (ppline->ppline_cmd[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

static void	print_echo_arg(t_ppline *ppline)
{
	int	i;

	i = 1;
	while (ppline->ppline_cmd[i])
	{
		if (ft_strncmp(ppline->ppline_cmd[i], "$?", 2) == 0)
		{
			printf(R "ECHO$? g_exit_status: %d\n" RS, g_exit_status);
			ft_putnbr_fd(g_exit_status, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			return ;
		}
		ft_putstr_fd(ppline->ppline_cmd[i], STDOUT_FILENO);
		if (ppline->ppline_cmd[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	print_and_return(t_ppline **ppline, int flag_echo, int flag_n)
{
	int	i;

	i = 0;
	if (flag_echo == 1)
	{
		write(1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	if (flag_n == 1)
	{
		if (!(*ppline)->ppline_cmd[i + 2])
			return (EXIT_SUCCESS);
		else
			print_echo_n_flag(*ppline, i + 2);
	}
	else
		print_echo_arg(*ppline);
	return (EXIT_SUCCESS);
}

// int	print_and_return(t_ppline **ppline, int flag_echo, int flag_n)
// {
// 	int	i;

// 	i = 0;
// 	if (flag_echo == 1)
// 	{
// 		write(1, "\n", 1);
// 		return (EXIT_SUCCESS);
// 	}
// 	if (flag_n == 1)
// 	{
// 		if (!(*ppline)->ppline_cmd[i + 2])
// 			return (EXIT_SUCCESS);
// 		else
// 		{
// 			i = i + 2;
// 			while ((*ppline)->ppline_cmd[i])
// 			{
// 				ft_putstr_fd((*ppline)->ppline_cmd[i], STDOUT_FILENO);
// 				if ((*ppline)->ppline_cmd[i + 1])
// 					ft_putchar_fd(' ', STDOUT_FILENO);
// 				i++;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		i = 1;
// 		while ((*ppline)->ppline_cmd[i])
// 		{
// 			if (ft_strncmp((*ppline)->ppline_cmd[i], "$?", 2) == 0)
// 			{
// 				printf(R "ECHO$? g_exit_status: %d\n" RS, g_exit_status);
// 				ft_putnbr_fd(g_exit_status, STDOUT_FILENO);
// 				ft_putchar_fd('\n', STDOUT_FILENO);
// 				return (EXIT_SUCCESS);
// 			}
// 			ft_putstr_fd((*ppline)->ppline_cmd[i], STDOUT_FILENO);
// 			if ((*ppline)->ppline_cmd[i + 1])
// 				ft_putchar_fd(' ', STDOUT_FILENO);
// 			i++;
// 		}
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 	}
// 	return (EXIT_SUCCESS);
// }
