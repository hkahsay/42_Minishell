#include "../../headers/minishell.h"

void	print_cmd(t_cmd *cmd)
{
	printf(YELLOW "CMD ARGS: " RS);

	t_wr_node *args = cmd->cmd_wnode;

	while (args != NULL)
    {
		printf(YELLOW "%s " RS, args->file);
		args = args->next;
	}

	printf(GREEN "\nCMD REDIR: " RS);
    
	t_wr_node *redir = cmd->cmd_rnode;

	while (redir != NULL)
	{
		printf(GREEN "%d:%s" RS, redir->type, redir->file);
		redir = redir->next;
	}
	printf("\n");
}

// void	print_wr_node(t_cmd *cmd, t_wr_node *cmd_wnode)
// {
// 	printf("CMD ARGS: ");

// 	t_wr_node *args = cmd->cmd_wnode;

// 	while (args != NULL)
//     {
// 		printf("%s ", args->file);
// 		args = args->next;
// 	}
// }

// void	print_pipeline(t_pipeline *pipeline)
// {
// 	while (pipeline != NULL) {
// 		printf("PIPELINE %d:\n", pipeline->cmd_index);
// 		t_cmd *cmd = pipeline->cmd_node;
// 		while (cmd != NULL) {
// 			print_cmd(cmd);
// 			cmd = cmd->next;
// 		}
// 		pipeline = pipeline->next;
// 	}
// }

// void print_cmd(t_cmd *cmd) {
//     printf("Command: %s\n", cmd->cmd_name);
//     printf("Arguments:\n");
//     t_redir_args *arg = cmd->cmd_args;
//     while (arg != NULL) {
//         printf("  %s\n", arg->file);
//         arg = arg->next;
//     }
//     printf("Redirections:\n");
//     t_redir_args *redir = cmd->cmd_redir;
//     while (redir != NULL) {
//         printf("  %s\n", redir->file);
//         redir = redir->next;
//     }
//     printf("\n");
// }