#include "../../headers/minishell.h"

// void execute(t_token **tok_cmd, t_envnode *mini_env) //t_pipeline *pipeline
// {
// 	char	**arg_cmds = NULL;
// 	(void)mini_env;
// 	(void)arg_cmds;
// 	printf(R "EXECUTE: " RS);
// 	// print_token(tok_cmd);
// 	print_cmd_list1(tok_cmd);
// 	// arg_cmds = create_array(&cmd);
// 	// printf("argcmd_exc %s\n", *arg_cmds);
// 	// if (is_builtin(arg_cmds, mini_env) == -1)
// 	// 	printf("NOT builtin\n");
// }

void execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env) //t_pipeline *pipeline
{
	t_pmd	*pmd;
	(void)mini_env;
	
	pmd = init_pmd();
	printf(R "EXECUTE: " RS);
	// print_cmd(cmd);
	print_cmd_list(cmd);
	pmd = create_array(&cmd, cmd_num);
	print_pmd_list(pmd);
	// printf("argcmd_exc %s\n", *arg_cmds);
	if (is_builtin(pmd->pmd_cmd, mini_env) == -1)
		printf("NOT builtin\n");
}

// void execute1(t_pline *pline, t_envnode *mini_env) //t_pipeline *pipeline
// {
// 	// char	**arg_cmds = NULL;
// 	// printf(R "EXECUTE: " RS);
// 	// print_cmd(cmd);
// 	// arg_cmds = create_array(&cmd);
// 	// printf("argcmd_exc %s\n", *arg_cmds);
// 	// if (is_builtin(arg_cmds, mini_env) == -1)
// 	// 	printf("NOT builtin\n");
// 	// printf("arg_cmds %s\n", *arg_cmds);
// 	printf(R "EXECUTE: " RS);
// 	(void)mini_env;
// 	t_pline	*pline_head = pline;
// 	// pline_head = malloc(sizeof(t_pline));
// 	// if (pline_head != NULL)
// 	// 	ft_memset(pline_head, 0, sizeof(t_pline));

// 	// print_pipeline(pline_head);

// 	// if (cmd && cmd->cmd_args && cmd->cmd_args->file)
// 	// {
// 	// 	while (cmd->cmd_args->next)
// 	// 	{
// 	// 		printf(GREEN "%s\n", cmd->cmd_args->next->file);
// 	// 		cmd->cmd_args->next = cmd->cmd_args->next->next;
// 	// 	}

// 	// }
// }


