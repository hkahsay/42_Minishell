#include"../../headers/minishell.h"

void print_ppline_list(t_ppline *ppline, int ppline_idx)
{
	int i;

	i = 1;
	t_ppline *current = ppline;
	while (current != NULL && 0 < ppline_idx)
	{
		i = 1;
		// printf("i from print_ppline_list: %d\n", i);
		printf("PPLINE_list_idx: %d\n", ppline_idx);
		printf("Command: %s\n", current->pp_first_cmd);
		printf("Command arguments:\n");
		while (current->ppline_cmd[i] != NULL)
		{
			printf("%s\n", current->ppline_cmd[i]);
			i++;
		}
		// printf_mini_env_array(current->ppline_env);
		printf("Redirections: %d\n", current->red_status);
		printf("Input file: %d\n", current->infile);
		printf("Output file: %d\n", current->outfile);
		printf("Heredoc: %d\n", current->heredoc);
		printf("Heredoc FDs: %d %d\n", current->hdoc_fd[0], current->hdoc_fd[1]);
		printf("\n");

		current = current->next;
		ppline_idx--;
	}
}
