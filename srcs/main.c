#include "../headers/minishell.h"

int	g_status = 0;


void	prompt(char	*line, t_envnode *mini_env) //t_envnode *my_envp,
{
	int		fd;
	struct termios saved;
	// t_token *token_head;
	// t_cmd	*cmd;
	// t_pipeline *pipeline;


	// token_head = NULL;
	// cmd = NULL;
	// pipeline = NULL;

	if (tcgetattr(STDIN_FILENO, &saved) == -1) 
    	perror("tcgetattr"); // handle error and return or exit as appropriate
	ter_attr_handler(saved);
	line = readline (GREEN "minishell_VH>> " RS);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);
	// index = getpid();
	if (!line)
	{
		printf("exit\n");	
		free(line);
		return ;
	}
	if (ft_strlen(line) > 0)
	{
		// printf("propmt line: %s\n", line);
		interp(line, mini_env);
		add_history(line);
		fd = open("history.log", O_CREAT | O_WRONLY | O_APPEND, 0777);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		close(fd);
		printf("\nMAIN: OK head is back\n");
		// cmd = parse(line, cmd);

	}
	else
		free(line);
}

int main(int argc, char **argv, char **envp)
{
	char		*line;
	t_envnode	*mini_envp;
	struct termios	saved;

	// t_mini		*mini;
	// t_envnode *temp;

	line = NULL;
	mini_envp = NULL;
	// temp = NULL;
	if (tcgetattr(STDIN_FILENO, &saved) == -1) 
    	perror("tcgetattr"); // handle error and return or exit as appropriate
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
	// temp = mini_envp;
	// print_mini_envp(temp);
	while (1)
	{
		sig_handlers();
		prompt(line, mini_envp); //my_envp,
	}
	// free_mini_envp(mini_envp);
	// my_free_all(t_malloc **head);
	return (0);
}

// ft_cd(built, my_envp);
// mini_pwd2(my_envp);
// ft_echo(cmd);
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
