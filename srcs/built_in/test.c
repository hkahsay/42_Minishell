#include"../../headers/minishell.h"
# include <string.h>

// int cd(char *path) {
//     int result = chdir(path);
//     if (result != 0) {
//         perror("cd");
//         return 1;
//     }
//     return 0;
// }

// int main() 
// {
//     char *input;

//     while (1)
// 	{
//         input = readline("> ");
// 		// getwd(input);
//         if (strcmp(input, "cd") == 0)
// 		{
// 			printf("%s\n", getenv("HOME"));
//         }
// 		else if (strcmp(input, "~") == 0)
// 		{
// 			printf("%s\n", getenv("HOME"));
//         }
// 		else if (strncmp(input, "cd -", 4) == 0)
// 		{
// 			printf("%s\n", getwd(input));
//         }
// 		else 
//             printf("Command not recognized\n");
//     }
	
//     return 0;
// }