#include "../../headers/minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd) * 1);
	printf(YELLOW "init new_cmd %p\n" RS, new_cmd);
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd_wnode = NULL;
	new_cmd->cmd_rnode = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

t_wr_node	*init_wr_node(t_wr_node *new_wr_node)
{
	new_wr_node = malloc(sizeof(t_wr_node) * 1);
	printf(GREEN "init: new_wr_node address %p\n" RS, new_wr_node);
	if (!new_wr_node)
		return (NULL);
	new_wr_node->type = 0;
	new_wr_node->file = NULL;
	new_wr_node->close_fd = 0;
	new_wr_node->next = NULL;
	printf(GREEN "init: new_wr_node content %p %s %d\n" RS, new_wr_node->file, new_wr_node->file, new_wr_node->type);
	return (new_wr_node);
}
