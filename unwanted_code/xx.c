
typedef struct s_cmd
{
	pid_t				process_id;
	char				*content;
	int					redir_out;
	int					redir_in;
	struct s_cmd		*next;
}	t_cmd;

int	is_word(const char *str)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (word);
		else
		{
			word++;
			i++;
		}
	}
	return (word);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->content = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_word	*init_word(char *content, int id)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (0);
	word->content = content;
	word->id = id;
	word->next = NULL;
	return (word);
}

t_blank	*white_space(char *content, int id)
{
	t_blank	*space;

	space = malloc(sizeof(t_blank));
	if (!space)
		return (0);
	space->content = content;
	space->id = id;
	space->next = NULL;
	return (space);
}

t_arg	*args(char *content, int id)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (0);
	arg->content = content;
	arg->id = id;
	arg->next = NULL;
	return (arg);
}

// char	*classification(t_token *token, char *content, int id)
// {
// 	// if (id == WORD)
// 	// 	token->content = word_token(content);
// 	else if (id == REDIR_OUT)
// 		token->content = NULL;
// 	else if (id == REDIR_IN)
// 		token->content = NULL;
// 	else if (id == REDIR_APPEND)
// 		token->content = NULL;
// 	else if (id == HERE_DOC)
// 		token->content = NULL;
// 	else if (id == PIPE)
// 		token->content = NULL;
// 	printf("token classification OK!\n");	
// 	return (0);
// }
