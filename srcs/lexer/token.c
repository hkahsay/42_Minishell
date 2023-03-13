

#include "../../headers/minishell.h"

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

// static t_list	*token_redir_append(t_list *token)
// {
// 	if (!token)
// 		return (0);
// 	token->content = ">>";
// 	token->id_token = 4;
// 	return (token);
// }

// static t_list	*init_token_quote(char *line, int *i)
// {
// 	t_list	*new;
// 	int		k;
// 	char	*content;

// 	k = *i;
// 	new = NULL;
// 	new = init_token(new);
// 	if (!new)
// 		return (0);
// 	while (line[*i])
// 	{
// 		if (line[*i] == 34)
// 		{
// 			while (line[*i] != 34)
// 			{
// 				// *i++;
// 			}					
// 		}
// 		else if (line[*i] == 39)
// 		{
// 			while (line[*i] != 39)
// 			{

// 			}	// *i++;		
// 		}
// 	}
// 	if (line[*i] == 34)
// 	{
// 		content = ft_substr(line, k, (*i - k));
// 		token_doublequote(new, content);
// 	}	
// 	else if (line[*i] == 39)
// 	{
// 		content = ft_substr(line, k, (*i - k));
// 		token_singlequote(new, content);
// 	}	
// 	else if (line[*i] == '\0')
// 		return (0);
// 	return (new);
// }

t_list	*create_list_token(char *epline) //, int id no reason for id, it prints always the same id
{
	t_list	*token;
	t_list	*head;
	t_list	*temp;
	int		i;

	token = NULL;
	head = NULL;
	temp = NULL;
	if (!epline)
		return (0);
	i = 0;
	while (epline[i]) //what is happening when we hit "enter": \0 or \n???
	{
		printf("epline[%d]: %c\n", i, epline[i]);
		if (((epline[i] == '>') || (epline[i] == '<') || (epline[i] == '|')) && epline[i + 1] != '\0') // && epline[i + 1] != '>'  && epline[i + 1] != '<'
		{
			init_token_redirect(epline, &i);
			printf("init token_redirect OK!\n");
		}
		// else if (epline[i] == 34 || epline[i] == 39)
		// {
		// 	init_token_quote(epline, &i);
		// 	printf("init token_quote OK!\n");
		// }
		else if (ft_isspace(epline[i]))
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
		printf("i token: %d\n", i);	
		i++;
	}
	return (head);
}
