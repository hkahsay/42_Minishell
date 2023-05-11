#include"../../headers/minishell.h"

void	print_cmd_list(t_cmd *cmd_list)
{
	int	i;

	i = 0;
	while (cmd_list != NULL)
	{
		printf("Command [%d]:\n", i);
		if (cmd_list->cmd_word)
			printf(YELS "%s\n" RS, cmd_list->cmd_word->content);
		printf("Command word:\n");
		if (cmd_list)
			print_token_list(cmd_list->cmd_word);
		printf("Redirections:\n");
		print_token_list(cmd_list->cmd_red);
		cmd_list = cmd_list->next;
		i++;
	}
}
