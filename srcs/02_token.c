

#include "../headers/minishell.h"

// t_list	*init_token(char *line)
// {
// 	t_list	*token;

// 	token = malloc(sizeof(t_list) * 1);
// 	if (!token)
// 		return (0);
// 	token->content = ft_strdup(line);
// 	token->id_token = classification(token, token->content);
// 	token->next = NULL;
// 	return (token);
// }

// int	classification(t_list *token, char *line)
// {
// 	// char *prnt_line;

// 	// if ((prnt_line = ft_isprint(line)))
// 	// 	return (0);

// 	int	i = 0;
// 	i = ft_strlen(line);
// 	if (i == 1)
// 	{
// 		if (line[i] == '>')
// 			return (2);
// 		else if (line[i] == '<')
// 			return (3);
// 		else if (line[i] == '|')
// 			return (6);
// 		else
// 			return (1);
// 		i++;	
// 	}
// 		else if (line[i] == '>>') // false, 2 signes here
// 			return (4);
// 		else if (line[i] == '<<') // false, 2 signes here
// 	return (0);
// }

static t_list	*init_token(t_list	*token)
{
	token = malloc(sizeof(t_list) * 1);
	if (!token)
		return (0);
	token->content = NULL;
	token->id_token = 0;
	token->next = NULL;
	return (token);
}

static t_list *init_token_redirect(char c)
{
	t_list	*new;

	new = NULL;
	new = init_token(new);
	if (c == '>')
	{
		new->content = ">";
		new->id_token = 2;
	}
	if (c == '<')
	{
		new->content = "<";
		new->id_token = 3;
	}
	if (c == '|')
	{
		new->content = "|";
		new->id_token = 6;
	}
	return (new);
}

t_list	*create_list_token(char *line) //, int id no reason for id, it prints always the same id
{
	t_list	*token;
	char **line_matrix;
	int	i = 0;
	// int	id_token = 0;

	token = NULL;
	if (!line[i])
		return (0);
	// printf("id token: %d\n", id);
	while(ft_isspace(line[i]))
		i++;
	printf("%c\n", line[i]);	
	while (line[i] != '\0' || line[i] != '\n') //what is happening when we hit "enter": \0 or \n???
	{
		if ((line[i] == '>' && line[i + 1] != '>') || (line[i] == '<' && line[i + 1] != '<') || line[i] == '|')
			init_token_redirect(line[i]);
		while (line[i] != '\0' && line[i] != '"') //not managing '', maybe not important
		{
			line_matrix = split_line(line, ' ');
			i++;
		}
	}
		
	printf("%d\n", i);
	// while (line[i])
	// {

	// 	token = init_token(line_matrix[i]);
	// 	printf("token init OK!\n");
	// 	printf("token->content: %s\n", token->content);
	// 	i++;
	// }
	
	
	// id = token->id_token;
	// token->content = content;
	// token->content = classification(token, content, id);
	return (token);
}
