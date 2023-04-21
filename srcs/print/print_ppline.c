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
		printf("PPline_index: %d\n", current->ppline_idx);
		// print_mini_env_array(current->pp_arr_env);
		// print_mini_envp(current->pp_list_env);
		printf("Redirections: %d\n", current->pp_red_status);
		printf("Input file: %d\n", current->pp_infile);
		printf("Output file: %d\n", current->pp_outfile);
		printf("Heredoc: %d\n", current->pp_heredoc);
		printf("Heredoc FDs: %d %d\n", current->pp_hdoc_fd[0], current->pp_hdoc_fd[1]);
		printf("\n");

		current = current->next;
		ppline_idx--;
	}
}
