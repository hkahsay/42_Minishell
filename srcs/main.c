#include "../headers/minishell.h"

void	prompt(char	*line) //t_envnode *my_envp, 
{
	t_list	*token;
	int		index;
	int		fd;

	line = readline ("minishell_VH>>");
	printf ("prompt head OK!\n");
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

static void print_my_envp(t_envnode *temp)
{
	int i = 0;

	while (temp)
	{
		printf("LIST: %s=%s\n", temp->key, temp->value);
		temp = temp->next;
		i++;
	}
	printf("%d\n", i);
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
