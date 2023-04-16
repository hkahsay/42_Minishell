#include "../../headers/minishell.h"

// g_mini.exit_status;

static void	execute_cmd(t_ppline *ppline, char **mini_env_array, char **cmd_path)
{
	// (void)mini;
	// (void)mini_env;
	// (void)cmd_path;
	// printf(GREEN "execution\n" RS);
	if (execve(*cmd_path, ppline->ppline_cmd, mini_env_array) == -1)
		msg_error(ft_strjoin(ppline->ppline_cmd[0], " : command not found\n"), 127);
	// return (0);
}

static char	*find_path(char **mini_env_array)
{
	while (ft_strncmp("PATH", *mini_env_array, 4))
		mini_env_array++;
	return (*mini_env_array + 5);
}

static int	search_path(t_ppline *ppline, char **mini_env_array, char **cmd_path)
{
	char	**path_array;
	int		i;
	char	*temp;

	i = 0;
	*cmd_path = find_path(mini_env_array);
	path_array = ft_split(*cmd_path, ':');
	i = 0;
	while (path_array[i])
	{
		temp = ft_strjoin(path_array[i], "/");
		*cmd_path = ft_strjoin(temp, ppline->ppline_cmd[0]);
		free(temp);
		if (!access(*cmd_path, F_OK))
			return (-1);
		i++;
	}
	return (0);
}

// static int	execute_cmd(t_mini	*mini, t_cmd *cmd, t_envnode *mini_env_array)
// {
// 	char	*cmd_path;

// 	cmd_path = NULL;
// 	if (is_builtin(mini->mini_cmd, mini_env) == -1)
// 	{
// 		printf("NOT builtin\n");
// 		if (!(search_path(mini, mini_env_array, &cmd_path)))
// 		{
// 			printf("NO PATH\n");
// 			return (-1);
// 		}
// 		printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
// 		execute_cmd(mini, mini_env_array, &cmd_path);
// 	}
// 	return (0);
// }

static int	prepare_redir(t_cmd **cmd, t_ppline **ppline)
{
	printf(YELLOW "PREPARE_redir: printing cmd_list\n ");
	// print_cmd(cmd);
	print_cmd_list(*cmd);
	printf(RS);
	(void)ppline;
	while (*cmd)
	{
		if ((*cmd)->cmd_red->id == TOK_REDIR_IN || (*cmd)->cmd_red->id == TOK_REDIR_OUT ||
			(*cmd)->cmd_red->id == TOK_REDIR_OUT_APPEND || (*cmd)->cmd_red->id == TOK_HEREDOC)
			printf(ORS "prepare_redir\n"RS);
		// else
		// 	return (0);	
		(*cmd) = (*cmd)->next;	
	}
	return (0);
}

int execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env)
{
	t_ppline	*ppline;
	char		*cmd_path;
	char		**mini_env_arr;
	cmd_path = NULL;
	// mini = init_mini();

	printf(R "EXECUTE: printing cmd_list");
	// print_cmd(cmd);
	print_cmd_list(cmd);
	printf(RS);
	mini_env_arr = ft_mini_env_array(mini_env, ft_mini_env_size(mini_env));
	// printf_mini_env_array(mini_env_array);
	ppline = create_ppline_array(&cmd, cmd_num, mini_env_arr); //, mini_env_arr
	prepare_redir(&cmd, &ppline);
	printf(PURPLE"EXECUTE: printing ppline_list\n");
	print_ppline_list(ppline);
	printf(RS);
	if (is_builtin(ppline->ppline_cmd, mini_env) == -1) //ppline->ppline_env
	{
		printf("NOT builtin\n");
		if (!(search_path(ppline, mini_env_arr, &cmd_path)))
		{
			printf("NO PATH\n");
			return (-1);
		}
		printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
		execute_cmd(ppline, mini_env_arr, &cmd_path);
	}
	return (0); //execute_cmd(mini, &cmd, mini_env)
}

// int execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env)
// {
// 	t_mini	*mini;
// 	char	*cmd_path;
// 	char	**mini_env_array;
// 	// (void)mini_env;
// 	cmd_path = NULL;
// 	// mini = init_mini();

// 	mini_env_array = ft_mini_env_array(mini_env, ft_mini_env_size(mini_env));
// 	printf_mini_env_array(mini_env_array);
// 	// printf(R "EXECUTE: " RS);
// 	// print_cmd(cmd);
// 	// print_cmd_list(cmd);
// 	mini = create_array(&cmd, cmd_num);
// 	printf(PURPLE"mini array\n"RS);
// 	print_mini_list(mini);
// 	if (is_builtin(mini->mini_cmd, mini_env) == -1)
// 	{
// 		printf("NOT builtin\n");
// 		if (!(search_path(mini, mini_env_array, &cmd_path)))
// 		{
// 			printf("NO PATH\n");
// 			return (-1);
// 		}
// 		printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
// 		execute_cmd(mini, mini_env_array, &cmd_path);
// 	}
// 	return (0); //execute_cmd(mini, &cmd, mini_env)
// }