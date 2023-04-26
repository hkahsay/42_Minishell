#include "../../headers/minishell.h"

void	*ft_handle_heredoc(t_ppline **new_ppline, t_token **ptr_cmd_red)
{
	(void)ptr_cmd_red;
	(void)new_ppline;
	printf(LBLUE "\nheredoc\n\n");
	#include "minishell.h"

// void handle_heredoc(t_ppline *ppline) {
//     if (ppline->pp_heredoc) {
//         int pipefd[2];
//         pid_t pid;

//         if (pipe(pipefd) == -1) {
//             perror("pipe");
//             exit(EXIT_FAILURE);
//         }

//         pid = fork();
//         if (pid == -1) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         } else if (pid == 0) {
//             // Child process
//             close(pipefd[1]);
//             dup2(pipefd[0], STDIN_FILENO);
//             close(pipefd[0]);

//             // Execute the command
//             execvp(ppline->ppline_cmd[0], ppline->ppline_cmd);
//             perror("execvp");
//             exit(EXIT_FAILURE);
//         } else {
//             // Parent process
//             close(pipefd[0]);
//             char *heredoc_text = readline("heredoc> ");
//             write(pipefd[1], heredoc_text, strlen(heredoc_text));
//             free(heredoc_text);
//             close(pipefd[1]);

//             int status;
//             if (waitpid(pid, &status, 0) == -1) {
//                 perror("waitpid");
//                 exit(EXIT_FAILURE);
//             }

//             if (WIFEXITED(status)) {
//                 ppline->pp_exit = WEXITSTATUS(status);
//             }
//         }
//     }
// }

	return (0);
}
