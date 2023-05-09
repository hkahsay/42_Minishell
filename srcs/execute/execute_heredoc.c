#include "../../headers/minishell.h"

// int execute_heredoc(t_ppline *ppline) {
//     int pipefd[2];
//     pid_t pid;
//     char buf[BUFSIZ];
//     ssize_t nread;

//     // Create pipe
//     if (pipe(pipefd) == -1) {
//         perror("pipe");
//         return -1;
//     }

//     // Fork a child process
//     if ((pid = fork()) == -1) {
//         perror("fork");
//         return -1;
//     }

//     if (pid == 0) {
//         // Child process

//         // Close read end of pipe
//         close(pipefd[0]);

//         // Redirect stdin to heredoc input
//         dup2(pipefd[1], STDIN_FILENO);

//         // Execute command
//         execvp(args[0], args);

//         // If execvp fails, exit with error code
//         perror("execvp");
//         exit(EXIT_FAILURE);
//     }

//     // Parent process

//     // Close write end of pipe
//     close(pipefd[1]);

//     // Write heredoc input to pipe
//     write(pipefd[0], heredoc, strlen(heredoc));

//     // Close pipe and wait for child process to finish
//     close(pipefd[0]);
//     waitpid(pid, NULL, 0);

//     return 0;
// }

// int execute_heredoc(t_ppline *ppline)
// {
//     printf(LBLUE "\nheredoc\n\n");
//     int pipefd[2];
//     pid_t pid = 0;
//     // char buf[1024];
//     int status;
// 		char *heredoc_text;

//     if ((ppline)->pp_heredoc_status == 1)
// 	{
//         // printf("CMD: %s\n", (ppline)->pp_first_cmd);
//         // printf("Command arguments:\n");
//         // int i = 0;
//         // while ((ppline)->ppline_cmd[i] != NULL)
// 		// {
//         //     printf("%s\n", (ppline)->ppline_cmd[i]);
//         //     i++;
//         // }
//         // printf("EOF: %s\n", (ppline)->pp_heredoc_eof);
// 		if (pipe(pipefd) == -1)
// 			msg_error("open file", errno);
// 		else if (pid == 0) //kid process
// 		{
// 			close(pipefd[1]);
// 			dup2(pipefd[0], STDIN_FILENO);
// 			close(pipefd[0]);
// 			// if (execute_pipe_cmd(ppline) == -1)
// 			// 	msg_error("execution pipe_cmd: ", errno);
// 		}
// 		else //parent process
// 		{
// 			close(pipefd[0]);
// 			heredoc_text = readline("heredoc> ");
// 			write(pipefd[1], heredoc_text, ft_strlen(heredoc_text));
// 			my_free(heredoc_text);
// 			close(pipefd[1]);
// 			if (waitpid(pid, &status, 0) == -1)
// 				msg_error("waitpid", errno);
// 			if (WIFEXITED(status))
// 				(ppline)->pp_exit = WEXITSTATUS(status);
// 		}
//         // if (pipe(pipefd) == -1)
//         //     msg_error("open pipe", errno);

//         // pid = fork();
//         // if (pid == -1)
//         //     msg_error("fork", errno);

//         // if (pid == 0)
// 		// { // child process
//         //     close(pipefd[1]); // close write end of pipe
//         //     dup2(pipefd[0], STDIN_FILENO); // redirect stdin to read end of pipe
//         //     close(pipefd[0]); // close read end of pipe
//         //     // execute_pipe_cmd(ppline); // read input from the pipeline
//         //     exit(0);
//         // } else
// 		// { // parent process
//         //     close(pipefd[0]); // close read end of pipe
//         //     while (fgets(buf, sizeof(buf), stdin))
// 		// 	{
//         //         if (strcmp(buf, (ppline)->pp_heredoc_eof) == 0)
//         //             break; // stop reading input if EOF marker is encountered
//         //         write(pipefd[1], buf, strlen(buf));
//         //     }
//         //     close(pipefd[1]); // close write end of pipe
//         //     if (waitpid(pid, &status, 0) == -1)
//         //         msg_error("waitpid", errno);
//         //     if (WIFEXITED(status))
//         //         (ppline)->pp_exit = WEXITSTATUS(status);
//         // }
//     }
//     (ppline)->pp_heredoc_status = 0;
//     return (1);
// }


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
// 			my-free(heredoc_text);
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
//             my_free(heredoc_text);
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
