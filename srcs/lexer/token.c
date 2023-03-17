

#include "../../headers/minishell.h"

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

static void print_token(t_list *temp)
{
	int i = 0;

	printf("i: %d\n", i);
	while (temp)
	{
		printf("TOKEN: %s=%d\n", temp->content, temp->id_token);
		temp = temp->next;
		i++;
	}
	printf("%d\n", i);
}

t_list	*init_token(t_list	*token)
{
	token = malloc(sizeof(t_list) * 1);
	if (!token)
		return (0);
	token->content = NULL;
	token->id_token = 0;
	token->next = NULL;
	return (token);
}

static int get_token_len(char *token)
{
    int len = 0;
    while (token[len] != '\0' && token[len] != '>' && token[len] != '<' && token[len] != '|')
        len++;
    return len;
}

t_list	*create_list_token(char *line) //, int id no reason for id, it prints always the same id
{
	t_list	*token;
	t_list	*head;
	t_list	*temp;
	t_list	*temp1;
	int		i;
	char **split;

	token = NULL;
	head = NULL;
	temp = NULL;
	if (!line)
		return (0);
	i = -1;
	split = ft_split_line(line);
	while (line[++i] != '\0') //what is happening when we hit "enter": \0 or \n???
	{	
		if ((line[i] == '>') || (line[i] == '<') || (line[i] == '|')) // && epline->str[i + 1] != '\0'  && epline[i + 1] != '>'  && epline[i + 1] != '<'
		{
			init_token_redirect(line, &i);
			if (!token)
				return (NULL);
			if (!head)
			{
				head = token;
				temp = head;
			}
			else
			{
				temp->next = token;
				temp = token;
			}
			printf("init token_redirect OK!\n");
		}
		else
		{
			token = init_token(token);
			if (!token)
				return (NULL);
			int len = get_token_len(&line[i]);
			printf("len word: %d\n", len);
			token->content = ft_substr(line, i, len);
			printf("token->content: %s\n", token->content);
			if (!token->content)
				return (NULL);
			// t_list *new = malloc(sizeof(t_list));
			// if (!new)
			// 	return NULL;

			// new->content = malloc(len + 1); // allocate memory for the token string
			// printf("new->content&: %p\n", new->content);
			// printf("new->content: %s\n", new->content);
			// if (!new->content) {
			// 	free(new);
			// 	return NULL;
			// }

			// strncpy(new->content, &line[i], len); // copy the token string into the new node
			// new->content[len] = '\0'; // add null terminator to the end of the token string

			// new->next = NULL; // initialize the next pointer to NULL	
			if (!head)
			{
				head = token;
				temp = head;
			}
			else
			{
				temp->next = token;
				temp = token;
			}
		}
	}
	temp1 = token;				
	print_token(token);	
	printf("i after token creation: %d\n", i);	
	return (head);
}

// t_list	*create_list_token(char *line) //, int id no reason for id, it prints always the same id
// {
// 	t_list	*token;
// 	t_list	*head;
// 	t_list	*temp;
// 	t_list	*temp1;
// 	int		i;

// 	token = NULL;
// 	head = NULL;
// 	temp = NULL;
// 	if (!line)
// 		return (0);
// 	i = -1;
// 	while (line[++i] != '\0') //what is happening when we hit "enter": \0 or \n???
// 	{
// 		// printf("line[%d] %d: %c\n", i, i, line[i]);
// 		if ((line[i] == '>') || (line[i] == '<') || (line[i] == '|')) // && epline->str[i + 1] != '\0'  && epline[i + 1] != '>'  && epline[i + 1] != '<'
// 		{
// 			init_token_redirect(line, &i);
// 			printf("init token_redirect OK!\n");
// 		}
// 		// else if (epline[i] == 34 || epline[i] == 39)
// 		// {
// 		// 	init_token_quote(epline, &i);
// 		// 	printf("init token_quote OK!\n");
// 		// }
// 		printf("token i: %d\n", i);
// 		// if (ft_isspace(line[i]))
// 		// 	i++;
// 		printf("token i: %d\n", i);
// 		// if (!token)
// 		// 	return (0);
// 		printf("token YES\n");
// 		if(!head) //list empty
// 		{
// 			head = token;
// 			head->next = NULL; //set the next pointer of the first node to NULL
// 			printf("head YES\n");	
// 		}
// 		else
// 		{
// 			printf("head2 YES\n");
// 			temp = head;
// 			while (temp->next)
// 				temp = temp->next;
// 			temp->next = token;
// 			temp->next = NULL; //set the next pointer of the new last node to NULL
			
// 		}
// 	}
// 	temp1 = token;				
// 	print_token(token);	
// 	printf("i after token creation: %d\n", i);	
// 	return (head);
// }
