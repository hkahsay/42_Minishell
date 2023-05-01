#include "../../headers/minishell.h"

// int	execute_heredoc(t_ppline *ppline) //, t_token **ptr_cmd_red
// {
// 	printf(LBLUE "\nheredoc\n\n");
// 	// (void)ptr_cmd_red;
// 	// (void)new_ppline;
// 	int pipefd[2];
//     pid_t pid = 0;
// 	char *heredoc_text;
// 	int status;
// 	int	i = 0;

// 	if ((ppline)->pp_heredoc_status == 1)
// 	{
// 		printf("CMD: %s\n", (ppline)->pp_first_cmd);
// 		printf("Command arguments:\n");
// 		while ((ppline)->ppline_cmd[i] != NULL)
// 		{
// 			printf("%s\n", (ppline)->ppline_cmd[i]);
// 			i++;
// 		}
// 		printf("EOF: %s\n", (ppline)->pp_heredoc_eof);
// 		if (pipe(pipefd) == -1)
// 			msg_error("open file", errno);
// 		else if (pid == 0) //kid process
// 		{
// 			close(pipefd[1]);
// 			dup2(pipefd[0], STDIN_FILENO);
// 			close(pipefd[0]);
// 			if (execute_pipe_cmd(ppline) == -1)
// 				msg_error("execution pipe_cmd: ", errno);
// 		}
// 		else //parent process
// 		{
// 			close(pipefd[0]);
// 			heredoc_text = readline("heredoc> ");
// 			write(pipefd[1], heredoc_text, ft_strlen(heredoc_text));
// 			free(heredoc_text);
// 			close(pipefd[1]);
// 			if (waitpid(pid, &status, 0) == -1)
// 				msg_error("waitpid", errno);
// 			if (WIFEXITED(status))
// 				(ppline)->pp_exit = WEXITSTATUS(status);
// 		}

// 	}	
// 	// else
// 	// 	return (0);
// 	(ppline)->pp_heredoc_status = 0;
// 	return (1);
// }








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

// 	return (0);
// }
