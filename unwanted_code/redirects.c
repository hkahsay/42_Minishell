#include "../../headers/minishell.h"

static t_token	*token_heredoc(t_token *token)
{
	if (!token)
		return (0);
	token->content = "<<";
	token->id = 5;
	return (token);
}

// static t_token	*token_singlequote(t_token *new, char *str)
// {
// 	if (!new)
// 		return (0);
// 	new->content = strdup(str);
// 	new->id = 8;
// 	return (new);	
// }

// static t_token	*token_doublequote(t_token *new, char *str)
// {
// 	if (!new)
// 		return (0);
// 	new->content = strdup(str);
// 	new->id = 7;
// 	return (new);	
// }

static void	*token_simple_redirect(char c, t_token *token)
{
	if (c == '>')
	{
		token->content = ">"; //not sur if need a content
		printf(">: %s\n", token->content);
		token->id = 2;
	}
	else if (c == '<')
	{
		token->content = "<";
		printf("token->content <: %s\n", token->content);
		token->id = 3;
		printf("token->id <: %d\n", token->id);
	}
	else if (c == '|')
	{
		token->content = "|";
		printf("|: %s\n", token->content);
		token->id = 6;
	}
	return (0);
	// return (token);
}

t_token *init_token_redirect(char *epline, int *i)
{
	t_token	*new;

	new = NULL;
	new = init_token(new);
	if (!new)
		return (0);
	// if (epline->str[*i])
	// {
	  	if ((epline[*i] == '>' && (epline[*i + 1] != '>' || epline[*i + 1] == '\0')))
		{
			token_simple_redirect(epline[*i], new);
			*i += 1;	
		}
		else if ((epline[*i] == '<' && (epline[*i + 1] != '<' || epline[*i + 1] == '\0')))
		{
			token_simple_redirect(epline[*i], new);
			*i += 1;	
		}
		else if ((epline[*i] == '|' && (epline[*i + 1] != '|' || epline[*i + 1] == '\0')))
		{
			token_simple_redirect(epline[*i], new);
			 *i += 1;	
		}
		else if (epline[*i] == '<' && epline[*i + 1] == '<')
		{
			token_heredoc(new);
			// printf("<<: %s\n", new->content);
			*i += 2;
		}
		else if (epline[*i] == '|' && epline[*i + 1] == '|')
		{
			printf("||: %s\n", "Fake Error message, logical operator doesn't have to be managed");
			return (0);
		}
		// *i += 1;

	return (new);
}
