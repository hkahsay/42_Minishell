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
		if (current->ppline_cmd)
		{
			while (current->ppline_cmd[i] != NULL)
			{
				printf("%s\n", current->ppline_cmd[i]);
				i++;
			}
		}	
		printf("PPline_index: %d\n", current->ppline_idx);
		// print_mini_env_array(current->pp_arr_env);
		// print_mini_envp(current->pp_list_env);
		printf("Redirections_status: %d\n", current->pp_red_status);
		// printf("Pp_pipe[0]: %d\n", current->pp_pipe[0]);
		// printf("Pp_pipe[1]: %d\n", current->pp_pipe[1]);
		printf("Input file: %d\n", current->pp_infile);
		printf("Output file: %d\n", current->pp_outfile);
		printf("Heredoc_status: %d\n", current->pp_heredoc_status);
		printf("Heredoc_eof: %s\n", current->pp_heredoc_eof);
		printf("pp_fd_in: %d\n", current->pp_fd_in);
		printf("pp_fd_out: %d\n", current->pp_fd_out);
		printf("EXIT_status: %d\n", current->pp_exit);
		// printf("Heredoc FDs: %d %d\n", current->pp_hdoc_fd[0], current->pp_hdoc_fd[1]);
		printf("\n");
		// if (current->next)
		// {

		current = current->next;
		ppline_idx--;
	// 	}
	}
}
