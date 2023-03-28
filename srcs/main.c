#include "../headers/minishell.h"

void	prompt(char	*line) //t_envnode *my_envp, 
{
	int		fd;
	t_token *token_head;
	t_cmd	*cmd;
	t_pipeline *pipeline;


	token_head = NULL;
	cmd = NULL;
	pipeline = NULL;
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
		token_head = interp(line);
		// args = eval_token(head);
		// while (head)
		// {
		// 	printf("Head content main: %s\n", head->content);
		// 	head = head->next;
		// }
		// head = head->next;
		cmd = parse(&token_head);
		pipeline = split_cmds_into_pipeline(cmd);
		// execute_pipeline(pipeline);
		free_token_list(token_head);
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

// t_token	*lexer(char *line);

// t_token	*interp(char *line)
// {
// 	t_token	*token_head;

// 	token_head = lexer(line);
// 	if (token_head)
// 		parse(&token_head);
// 	return (token_head);
// }

/*t_token *tokens = tokenize_input(input_string);
t_cmd *cmds = split_tokens_into_cmds(&tokens);
t_pipeline *pipeline = split_cmds_into_pipeline(cmds);

free_token_list(tokens);*/

int main(int argc, char **argv, char **envp)
{
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
