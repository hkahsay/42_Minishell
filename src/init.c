#include"../minishell.h"
                                                                                                                                                                #include"../minishell.h"
t_list	*init_token(void)
{
	t_list	*token;

	token = malloc(sizeof(t_list) + 1);
	if (!token)
		return (0);
	token->id_token = 1;
	token->content = NULL;
	token->next = NULL;
	return (token);
}

t_list	*create_token(char *content, int id)
{
	t_list	*token;

	token = init_token();
	id = token->id_token;
	token->content = classification(token, content, id);
	return (0);
}

char	*classification(t_list *token, char *content, int id)
{
	if (id == WORD)
		token->content = word_token(content);
	else if (id == REDIR_OUT)
		token->content = NULL;
	else if (id == REDIR_IN)
		token->content = NULL;
	else if (id == REDIR_APPEND)
		token->content = NULL;
	else if (id == HERE_DOC)
		token->content = NULL;
	else if (id == PIPE)
		token->content = NULL;
	return (0);
}

int is_word(char *str)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (is_space(str[i]))
			return (word);
		else
		{
			word++;
			i++;
		}
	}
	return (word);
}

char	*word_token(char *word)
{
	int		i;
	int		n;
	char	*dest;
	char	**line;

	i = 0;
	i = is_word(word);
	line = ft_split(word, '|');
	printf("%s\n", line[0]);
	if (!word)
		return (0);
	n = ft_strlen(word);
	while (word[i] && i < n)
	{
		dest = strndup(word, n);
		i++;
	}
	return (dest);
}
