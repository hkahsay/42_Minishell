#include "../../headers/minishell.h"

void execute(t_cmd *cmd) //t_pipeline *pipeline
{
	printf(R "EXECUTE: " RS);
	print_cmd(cmd);
	// print_pipeline(pipeline);
	// if (cmd && cmd->cmd_args && cmd->cmd_args->file)
	// {
	// 	while (cmd->cmd_args->next)
	// 	{
	// 		printf(GREEN "%s\n", cmd->cmd_args->next->file);
	// 		cmd->cmd_args->next = cmd->cmd_args->next->next;
	// 	}
		
	// }
}