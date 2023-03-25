#include "../../headers/minishell.h"

// void	parse(t_token *head)
// {
// 		print_token(head);
// }

t_cmd	*tok_parser(char *input)
{
	t_token		*token;
	// t_toktype	type;
	t_cmd		*parse;
	char		*temp;

	//call token creation from lexer
	// type = 0;
	token = new_token(input, type);
	// parse = malloc(sizeof(t_cmd) * 1);
	// if (!parse)
	// {
	// 	printf("errpt\n");
	// 	// return (0);
	// }
	parse = NULL;
	// parser = interp(input);
	init_parser(parse);
	// temp = skip_spaces(input);
	printf("init ok\n");
	temp = input;
	printf(R"input is okay %s\n"RS, temp);

	while (*temp)
	{
		temp = new_parser(parse, temp);
		if (interp(input))
		{
			// add_parser
			printf(OR"ready to add\n"RS);
		}
		else
			printf ("Command not found: %s\n", temp);
		// printf(OR"parse->input44\n"RS);
		// printf(OR"tempbh %s\n"RS, temp);
		temp++;
	}
	return (0);
}

t_parser	*init_parser(t_parser *parse)
{
	parse = malloc(sizeof(t_cmd) * 1);
	if (!parse)
		return (0);
	parse->input = NULL;
	parse->index = 0;
	return (parse);
}

char	*new_parser(t_parser *parse, char *line)
{
	char	*str;
	char	*temp;

	// parse = NULL;
	parse = init_parser(parse);
	temp = ft_strdup(line);
	printf(GRAY"parse->input %p\n"RS, temp);
	str = temp;
	str = skip_spaces(temp);
	parse->input = str;
	printf(OR"parse->input 4 %s\n", parse->input);
	// free(temp);
	// free(line);
	printf(GGREEN"parse->input  %p\n"RS, str);
	return(str);
}

// void add_parser(t_parser **head, char *content, t_toktype type)
// {
//     t_token *token = new_token(content, type);

// 	// if (!token)
// 	// 	return (0);
//     if (*head == NULL)
//     {
//         *head = token;
//     }
//     else
//     {
// 		t_token *current = *head;
// 		while (current->next != NULL)
//         {
//             current = current->next;
//         }
//         current->next = token;
//     }
// }