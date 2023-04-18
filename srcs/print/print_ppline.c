#include"../../headers/minishell.h"

// void print_mini_list(t_mini *mini_list)
// {
// 	int i;
// 	t_mini *mini_curr;

// 	i = 0;
// 	mini_curr = mini_list;
// 	while (mini_curr != NULL)
// 	{
// 		printf(ORS "Command: %s \n" RS, mini_curr->cmd);
// 		printf(YELS "Command arguments: \n");
// 		while (mini_curr->mini_cmd[i])
// 		{
// 			printf("%s\n", mini_curr->mini_cmd[i]);
// 			i++;
// 		}
// 		// for (int i = 0; mini_curr->mini_cmd[i] != NULL; i++) {
// 		// 	printf("%s\n", mini_curr->mini_cmd[i]);
// 		// }
// 		printf(BLUE "Redirections: ");
// 		printf("Input file: %d\n", mini_curr->infile);
// 		printf("Heredoc: %d\n", mini_curr->heredoc);
// 		printf("Heredoc FDs: %d %d\n", mini_curr->hdoc_fd[0], mini_curr->hdoc_fd[1]);
// 		printf("\n");

// 		mini_curr = mini_curr->next;
// 	}
// }

// void print_one_ppline(t_ppline *ppline)
// {
// 	int i;

// 	i = 0;
// 	t_ppline *current = ppline;
// 	while (current != NULL)
// 	{
// 		printf("Command: %s\n", current->pp_first_cmd);
// 		printf("Command arguments:\n");
// 		printf("%s\n", current->ppline_cmd[0]);
// 		// printf_mini_env_array(current->ppline_env);
// 		// while (current->ppline_cmd[i + 1] != NULL)
// 		// {
// 		// 	printf("%s\n", current->ppline_cmd[i]);
// 		// 	i++;
// 		// }
// 		printf("Redirections:\n");
// 		printf("Input file: %d\n", current->infile);
// 		printf("Heredoc: %d\n", current->heredoc);
// 		printf("Heredoc FDs: %d %d\n", current->hdoc_fd[0], current->hdoc_fd[1]);
// 		printf("\n");

// 		current = current->next;
// 	}
// }


void print_ppline_list(t_ppline *ppline, int ppline_idx)
{
	int i;

	i = 1;
	t_ppline *current = ppline;
	while (current != NULL && 0 < ppline_idx)
	{
		i = 1;
		printf("i from print_ppline_list: %d\n", i);
		printf("ppline_idx from print_ppline_list: %d\n", ppline_idx);
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
