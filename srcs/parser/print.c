#include "../../headers/minishell.h"

void	print_cmd(t_cmd *cmd)
{
	printf("CMD ARGS: ");

	t_redir_args *args = cmd->cmd_args;

	while (args != NULL)
    {
		printf("%s ", args->file);
		args = args->next;
	}

	printf("\nCMD REDIR: ");
    
	t_redir_args *redir = cmd->cmd_redir;

	while (redir != NULL)
	{
		printf("%d:%s ", redir->type, redir->file);
		redir = redir->next;
	}
	printf("\n");
}

void	print_pipeline(t_pipeline *pipeline)
{
	while (pipeline != NULL) {
		printf("PIPELINE %d:\n", pipeline->cmd_index);
		t_cmd *cmd = pipeline->cmd_node;
		while (cmd != NULL) {
			print_cmd(cmd);
			cmd = cmd->next;
		}
		pipeline = pipeline->next;
	}
}

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