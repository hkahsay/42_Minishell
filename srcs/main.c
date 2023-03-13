#include "../headers/minishell.h"

void	prompt(char	*line) //t_envnode *my_envp, 
{
	t_list	*token;
	// int		index;
	int		fd;
	char *epline;

	line = readline ("minishell_VH>>");
	// printf ("prompt head OK!\n");
	// printf ("line to sent to tokeniser: %s\n", line);
	// index = getpid();
	if (!line)
	{
		printf("exit\n");
		free(line);
	}
	if (ft_strlen(line) > 0)
	{
		epline = ft_strdup(epur_str(line));
		if (!epline)
			return ;
		// printf("epured_line: %s\n", epline);
		token = create_list_token(epline); //, index
		add_history(line);
		fd = open("history.log", O_CREAT | O_WRONLY | O_APPEND, 0777);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	else
		free(line);
}

int main(int argc, char **argv, char **envp)
{
	// printf("MINISHELL\n");
	// int i = -1;
	// while (envp[++i])
	// 	printf("%s\n", envp[i]);
	// printf("%d\n", i);

	(void)argv;
	char	*line;
	t_envnode *my_envp;
	line = NULL;
	my_envp = NULL;
	t_envnode *temp = NULL;

	if (argc != 1 || !argv || !envp)
	{
		printf("Error arguments\n");
		return (-1);
	}
	my_envp = dublicate_env(envp);
	if (!my_envp)
	{
		printf("Failed to create my_environment list\n");
		return (1);
	}
	temp = my_envp;
	print_my_envp(temp);
	while (1)
		prompt(line); //my_envp, 
	free_myenvp(my_envp);	
	return (0);
}
