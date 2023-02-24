
#include "minishell.h"

/*1.initialise reserved_words, envp, envp_list
2.1.while(!exit_flag): readline, ft_readline?, add to history if there is a line
2.2.module: lexer: divides str in tokens. 
2.3.with lexer get info out of tokens, divide them into input, output, args, 
type ocommands: pipeline or standart commends..
2.4.execution: when we know everything about command, launch it, wait to execute,
exit
3.destruct: free all resources
*/
int	main(void)
{
	char	*str;

	str = readline("prompt> ");
	while (str) //if the line is not empty it has to be added to history
	{
		printf("%s\n", str);
		if (str)
			add_history(str);
		// return (str);	
	}
	return (0);	
}