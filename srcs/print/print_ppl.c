#include"../../headers/minishell.h"

void	print_ppl_list(t_ppl *ppl, int ppl_idx)
{
	int			i;
	t_ppl	*current;

	i = 1;
	current = ppl;
	while (current != NULL && 0 < ppl_idx)
	{
		i = 1;
		printf("ppl_list_idx: %d\n", ppl_idx);
		printf("Command: %s\n", current->pp_first_cmd);
		printf("Command arguments:\n");
		if (current->ppl_cmd)
		{
			while (current->ppl_cmd[i] != NULL)
			{
				printf("%s\n", current->ppl_cmd[i]);
				i++;
			}
		}	
		printf("ppl_index: %d\n", current->ppl_idx);
		printf("Redirections_status: %d\n", current->pp_red_status);
		printf("Input file: %d\n", current->pp_infile);
		printf("Output file: %d\n", current->pp_outfile);
		printf("Heredoc_status: %d\n", current->pp_heredoc_status);
		printf("Heredoc_eof: %s\n", current->pp_heredoc_eof);
		printf("pp_fd_in: %d\n", current->pp_fd_in);
		printf("pp_fd_out: %d\n", current->pp_fd_out);
		printf("EXIT_status: %d\n", current->pp_exit);
		printf("\n");
		current = current->next;
		ppl_idx--;
	}
}

