#include "../../headers/minishell.h"

void execute(t_cmd *cmd)
{
	if (cmd && cmd->cmd_args && cmd->cmd_args->args)
	{
		while (cmd->cmd_args->next)
		{
			printf(GREEN "%s\n", cmd->cmd_args->next->args);
			cmd->cmd_args->next = cmd->cmd_args->next->next;
		}
		
	}
}