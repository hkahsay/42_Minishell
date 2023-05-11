#include "../headers/minishell.h"

static void	history_log(char *line, int fd)
{
	add_history(line);
	fd = open("history.log", O_CREAT | O_WRONLY | O_APPEND, 0777);
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
	close(fd);
}

void	prompt(char	*line, t_envnode *mini_env)
{
	int	fd;

	fd = 0;
	signal_at_beginning();
	ter_attr_handler_off();
	line = readline (GREEN "minishell_VH>> " RS);
	ter_attr_handler_on();
	if (!line)
	{
		printf("exit\n");
		free(line);
		exit(0);
		return ;
	}
	if (ft_strlen(line) > 0)
	{
		interp(line, mini_env);
		signal(SIGINT, signal_handler2);
		history_log(line, fd);
		free(line);
	}
	else
		free(line);
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_envnode		*mini_envp;
	struct termios	saved;

	line = NULL;
	mini_envp = NULL;
	if (tcgetattr(STDIN_FILENO, &saved) == -1)
		perror("tcgetattr");
	if (argc != 1 || !argv || !envp)
	{
		printf("Error arguments\n");
		return (-1);
	}
	mini_envp = duplicate_env(envp);
	if (!mini_envp)
	{
		printf("Failed to create my_environment list\n");
		return (1);
	}
	while (1)
		prompt(line, mini_envp);
	write(1, "exit\n", 6);
	free(line);
	exit (0);
}
