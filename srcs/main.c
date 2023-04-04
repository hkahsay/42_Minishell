#include "../headers/minishell.h"

void	prompt(char	*line, t_envnode *mini_env) //t_envnode *my_envp, 
{
	int		fd;
	// t_token *token_head;
	// t_cmd	*cmd;
	// t_pipeline *pipeline;


	// token_head = NULL;
	// cmd = NULL;
	// pipeline = NULL;
	line = readline ("minishell_VH>> 😜 ");
	// index = getpid();
	if (!line)
	{
		printf("exit\n");
		free(line);
	}
	if (ft_strlen(line) > 0)
	{
		printf("propmt line: %s\n", line);
		interp(line, mini_env);
		ft_cd(built, my_envp);
		mini_pwd2(my_envp);
		ft_echo(cmd);
		// token_head = interp(line);
		// args = eval_token(head);
		// while (head)
		// {
		// 	printf("Head content main: %s\n", head->content);
		// 	head = head->next;
		// }
		// head = head->next;
		// cmd = parse(token_head);
		// pipeline = split_cmds_into_pipeline(cmd);
		// execute_pipeline(pipeline);
		printf("OK head is back\n");
		add_history(line);
		fd = open("history.log", O_CREAT | O_WRONLY | O_APPEND, 0777);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		// cmd = parse(line, cmd);
		
	}
	else
		free(line);
}

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	char	*line;
	t_envnode *mini_envp;
	line = NULL;
	mini_envp = NULL;
	t_envnode *temp = NULL;

	if (argc != 1 || !argv || !envp)
	{
		printf("Error arguments\n");
		return (-1);
	}
	mini_envp = dublicate_env(envp);
	if (!mini_envp)
	{
		printf("Failed to create my_environment list\n");
		return (1);
	}
	temp = mini_envp;
	print_mini_envp(temp);
	while (1)
		prompt(line, mini_envp); //my_envp, 
	free_mini_envp(mini_envp);	
	return (0);
}
