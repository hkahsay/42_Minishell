#include "../minishell.h"


void	prompt(char	*line)
{
	t_list	*token;
	int		index;
	int		fd;

	line = readline ("minishell_VH>>");
	index = getpid();
	if (!line)
	{
		printf("exit\n");
		free(line);
	}
	if (ft_strlen(line) > 0)
	{
		token = create_token(line, index);
		add_history(line);
		fd = open("history.log", O_CREAT | O_WRONLY | O_APPEND, 0777);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	else
		free(line);
}

int	main(void)
{
	char	*line;

	line = NULL;
	while (1)
	{
		prompt(line);
	}
}