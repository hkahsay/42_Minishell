#include "../../headers/minishell.h"

// static t_list	*token_heredoc(t_list *token)
// {
// 	if (!token)
// 		return (0);
// 	token->content = "<<";
// 	token->id_token = 5;
// 	return (token);
// }

// static t_list	*token_singlequote(t_list *new, char *str)
// {
// 	if (!new)
// 		return (0);
// 	new->content = strdup(str);
// 	new->id_token = 8;
// 	return (new);	
// }

// static t_list	*token_doublequote(t_list *new, char *str)
// {
// 	if (!new)
// 		return (0);
// 	new->content = strdup(str);
// 	new->id_token = 7;
// 	return (new);	
// }

static t_list	*token_simple_redirect(char c, t_list *token)
{
	if (c == '>')
	{
		token->content = ">"; //not sur if need a content
		printf(">: %s\n", token->content);
		token->id_token = 2;
	}
	else if (c == '<')
	{
		token->content = "<";
		printf("<: %s\n", token->content);
		token->id_token = 3;
	}
	else if (c == '|')
	{
		token->content = "|";
		printf("<: %s\n", token->content);
		token->id_token = 6;
	}
	return (token);
}

static t_list *init_token_redirect(char *line, int *i)
{
	t_list	*new;

	new = NULL;
	new = init_token(new);
	if (!new)
		return (0);
	if (line[*i])
	{
		if ((line[*i] == '>' && (line[*i + 1] != '>' || line[*i + 1] == '\0')))
		{
			token_simple_redirect(line[*i], new);
			*i += 1;	
		}
		else if ((line[*i] == '<' && (line[*(i + 1)] != '<' || line[*i + 1] == '\0')))
		{
			token_simple_redirect(line[*i], new);
			*i += 1;	
		}
		else if ((line[*i] == '|' && (line[*i + 1] != '|' || line[*i + 1] == '\0')))
		{
			token_simple_redirect(line[*i], new);
			*i += 1;	
		}
		else if (line[*i] == '<' && line[*i + 1] == '<')
		{
			token_heredoc(new);
			printf("<<: %s\n", new->content);
			*i += 2;
		}
		else if (line[*i] == '>' && line[*i + 1] == '>')
		{
			token_redir_append(new);
			printf(">>: %s\n", new->content);
			*i += 2;
		}
		else if (line[*i] == '|' && line[*i + 1] == '|')
		{
			printf("||: %s\n", "Fake Error message, logical operator doesn't have to be managed");
			return (0);
		}
		
	}
	return (new);
}
