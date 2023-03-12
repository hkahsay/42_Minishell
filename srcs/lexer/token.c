

#include "../../headers/minishell.h"

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

// static t_list *init_token_word(char *line, int *i)
// {
// 	t_list *new;
	
// 	new = NULL;
// 	new = init_token(new);
// 	while (line[*i] != '\0' && !ft_isspace(line[*i]))
// 	{
// 		if (line[*i] != '\0' && line[*i] != 32 && line[*i] != 39)
// 			*i++;
// 	}
	

// }

static t_list *init_token_redirect(char *line, int *i)
{
	t_list	*new;

	new = NULL;
	new = init_token(new);
	if (line[*i] == '>') // 
	{

		// if (line[*(i + 1)] != '\0' || (*(i + 1) < (int)ft_strlen(line) && line[*(i + 1)] != '>'))
		// {
			new->content = ">";
			printf(">: %s\n", new->content);
			new->id_token = 2;
			*i += 1;
		// }		
	}
	else if (line[*i] == '>' && line[*(i + 1)] == '>')
	{
		new->content = ">>";
		printf(">: %s\n", new->content);
		new->id_token = 4;
		*i += 1;
	}
	else if (line[*i] == '<' && line[*(i + 1)] != '<')
	{
		new->content = "<";
		printf("<: %s\n", new->content);
		new->id_token = 3;
		*i += 2;
	}
	else if (line[*i] == '<' && line[*(i + 1)] == '<')
	{
		new->content = "<<";
		printf("<: %s\n", new->content);
		new->id_token = 3;
		*i += 2;
	}
	else if (line[*i] == '|')
	{
		new->content = "|";
		printf("|: %s\n", new->content);
		new->id_token = 6;
		*i += 1;
	}	
	return (new);
}

t_list	*create_list_token(char *line) //, int id no reason for id, it prints always the same id
{
	t_list	*token;
	t_list	*head;
	t_list	*temp;
	// char **line_matrix;
	char	*epline;
	int	i = 0;
	// int	id_token = 0;

	token = NULL;
	head = NULL;
	temp = NULL;
	if (!line)
		return (0);
	// printf("id token: %d\n", id);
	printf("line: %s\n", line);	
	epline = epur_str(line); // ft_isprint????
	if (!epline)
		return (0);
	printf("epured_line: %s\n", epline);
	printf("i token: %d\n", i);	
	while (epline[i] != '\0') //what is happening when we hit "enter": \0 or \n???
	{
		// if (epline[i] != '\0' && epline[i] != 62 && epline[i] != 60 && epline[i] != 6) // && epline[i] != 39 && epline[i] != 34
		// {
		// 	init_token_word(epline, &i);
		// 	printf("init token_word OK!");
		// }
		if ((epline[i] == '>') || (epline[i] == '<') || (epline[i] == '|')) // && epline[i + 1] != '>'  && epline[i + 1] != '<'
		{
			init_token_redirect(epline, &i);
			printf("init token_redirect OK!\n");
		}
		if (ft_isspace(epline[i]))
			i++;
		if (!token)
			return (0);
		if(!head)
			head = token;
		else
		{
			temp = head;
			while (temp->next)
				temp = temp->next;
			temp->next = token;
			temp = token;
		}			
		// while (epline != '\0' && epline != 34) //not managing '', maybe not important line[i] != 39 = ' line[i] != 34 = ""
		// {
		// 	line_matrix = split_line(epline, ' ');
		// 	i++;
		// }
	}
		
	// printf("%d\n", i);
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
	return (head);
}
