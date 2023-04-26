#include "../../headers/minishell.h"

t_cmd *init_cmd(void)
{
	t_cmd *new_cmd;

	new_cmd = (t_cmd *)my_malloc(sizeof(t_cmd));
	// printf(YELLOW "init new_cmd %p\n" RS, new_cmd);
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->cmd_word = NULL;
	new_cmd->cmd_red = NULL;
	new_cmd->next = NULL;

	return (new_cmd);
}

