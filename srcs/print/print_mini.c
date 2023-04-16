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

void print_ppline_list(t_ppline *ppline)
{
    t_ppline *current = ppline;
    while (current != NULL) {
        printf("Command: %s\n", current->pp_first_cmd);
        printf("Command arguments:\n");
        for (int i = 0; current->ppline_cmd[i] != NULL; i++) {
            printf("%s\n", current->ppline_cmd[i]);
        }
        printf("Redirections:\n");
        printf("Input file: %d\n", current->infile);
        printf("Heredoc: %d\n", current->heredoc);
        printf("Heredoc FDs: %d %d\n", current->hdoc_fd[0], current->hdoc_fd[1]);
        printf("\n");

        current = current->next;
    }
}
