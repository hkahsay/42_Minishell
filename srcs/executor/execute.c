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

// typedef struct    s_list
// {
//    struct s_list *next;
//    void          *data;
// }                 t_list;

// int ft_list_size(t_list *begin_list)
// {
//    if (begin_list == 0)
//        return (0);
//    else
//        return (1 + ft_list_size(begin_list->next));
// }

// ft_strlen(cmd->cmd_wnode->file);