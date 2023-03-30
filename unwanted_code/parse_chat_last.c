#include "../../headers/minishell.h"

static t_cmd	*init_cmd(void)
{
	t_cmd	*new_cmd;
	
	new_cmd = malloc(sizeof(t_cmd) * 1);
	printf("new_cmd %p\n", new_cmd);
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd_word_node = NULL;
	new_cmd->cmd_redir_node = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

static t_word_redir_list	*init_word_redir_node(t_word_redir_list *new_wr_node)
{
	new_wr_node = malloc(sizeof(t_word_redir_list) * 1);
	printf("new_wr_node address %p\n", new_wr_node);
	if (!new_wr_node)
		return (NULL);
	new_wr_node->type = 0;
	new_wr_node->file = NULL;
	new_wr_node->close_fd = 0;
	new_wr_node->next = NULL;
	printf("new_wr_node content %p %s %d\n", new_wr_node->file, new_wr_node->file, new_wr_node->type);
	return (new_wr_node);
}

// static t_redir_args *new_redir_args(char *content, t_toktype type)
// {
// 	t_redir_args *new_args = NULL;
// 	new_args = init_args(new_args);
// 	new_args->type = type;
// 	new_args->file = ft_strdup(content);
// 	new_args->next = NULL;
// 	return (new_args);
// }

static t_word_redir_list	*fill_word_redir_node(char *file, t_toktype type)
{
	t_word_redir_list *new_wr_node;

	new_wr_node = malloc(sizeof(t_word_redir_list) * 1);
	printf("new_wr_node %p %s %d\n", new_wr_node->file, new_wr_node->file, new_wr_node->type);
	if (!new_wr_node)
		return (NULL);
	new_wr_node->type = type;
	new_wr_node->file =ft_strdup(file);
	new_wr_node->close_fd = 0;
	printf("new_wr_node content %p %s %d\n", new_wr_node->file, new_wr_node->file, new_wr_node->type);
	new_wr_node->next = NULL;
	return (new_wr_node);
}

static t_word_redir_list *add_redir_to_cmd_list(t_word_redir_list **head_wr_node, t_word_redir_list *redir_list)
{
	t_word_redir_list	*new_redir;
	t_word_redir_list	*current;

	new_redir = fill_word_redir_node((*head_wr_node)->next->file, (*head_wr_node)->type);
	*head_wr_node = (*head_wr_node)->next;
	if (!redir_list)
		redir_list = new_redir;
	else
	{
		current = redir_list;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
	return (redir_list);
}

static t_word_redir_list *add_word_to_cmd_list(t_word_redir_list **head_wr_node, int type, char *content)
{
	t_word_redir_list *new_wr_node = NULL;
	t_word_redir_list *current;
	
	current = NULL;
	new_wr_node = init_word_redir_node(new_wr_node);
	new_wr_node = fill_word_redir_node(content, type);
	if (!new_wr_node)
		return (NULL);
	if (*head_wr_node == NULL)
		*head_wr_node = new_wr_node;
	else
	{
		current = *head_wr_node;
		while (current->next)
			current = current->next;
		current->next = new_wr_node;
	}
	return (*head_wr_node);
}

static void	eval_token(t_token *head, t_cmd **cmd, t_pipeline **pipeline_head, t_cmd **pipeline_cmd_tail)
{
	t_word_redir_list *wr_node = NULL;
	t_token *_head;
	*cmd = init_cmd();
	wr_node = init_word_redir_node(wr_node);
	printf("init cmd OK\n");
	// int i = 2;
	// int j = 0;
	
	// wr_node = NULL;
	_head = head;
	while (_head && (t_toktype)(_head->id) != TOK_PIPE)
	{
		printf("1\n");
		print_cmd(*cmd);
		if (_head->id == TOK_WORD || _head->id == TOK_D_QUOTE || _head->id == TOK_S_QUOTE) //(head_ptr->id != TOK_PIPE)
		{
			printf("2\n");
			while (_head && (_head->id == TOK_WORD || _head->id == TOK_D_QUOTE || _head->id == TOK_S_QUOTE)) // || head_ptr->id == TOK_DOLLAR
			{
				printf("3\n");
				if (_head->id == TOK_WORD) //!= TOK_D_QUOTE && _head->id != TOK_S_QUOTE
				{
					printf("TOK_WORD %p %s %d\n", _head->content, _head->content, _head->id);
					// wr_node = init_word_redir_node(wr_node);
					printf(R "returned from init word OK\n" RS);
                    // wr_node->type = _head->id;
                    // wr_node->file = ft_strdup(_head->content);
					(*cmd)->cmd_word_node = add_word_to_cmd_list(&(*cmd)->cmd_word_node, wr_node->type, wr_node->file);
					printf("4\n");
				}
				else if (_head->id == TOK_D_QUOTE)
				{
					printf("Have to manage D_QUOTE\n");
				}
				else if (_head->id == TOK_S_QUOTE)
				{
					printf("Have to manage S_QUOTE\n");
				}
				else if (_head && (_head->id == TOK_REDIR_IN || _head->id == TOK_REDIR_OUT || _head->id == TOK_REDIR_OUT_APPEND ||
					_head->id == TOK_HEREDOC))
				{
					printf("5\n");
					//still have to manage the quote part
					if (wr_node)
					{
						printf("6\n");
						(*cmd)->cmd_redir_node = add_redir_to_cmd_list(&(*cmd)->cmd_redir_node, wr_node);
						wr_node = NULL;
					}
					wr_node = fill_word_redir_node(_head->content, _head->id);
				}
				printf("7\n");
				wr_node = init_word_redir_node(wr_node);
				printf(R "init_args OK" RS);
				wr_node->type = _head->id;
				wr_node->file = ft_strdup(_head->next->content);
				_head = _head->next;
			}
		}
		else if (_head && (_head->id == TOK_REDIR_IN || _head->id == TOK_REDIR_OUT || _head->id == TOK_REDIR_OUT_APPEND ||
			_head->id == TOK_HEREDOC))
		{
			// handle input/output redirection
			printf("8\n");
			if (wr_node)
			{
				printf("9\n");
				(*cmd)->cmd_redir_node = add_redir_to_cmd_list(&(*cmd)->cmd_redir_node, wr_node);
				wr_node = NULL;
			}
			printf("10\n");
			wr_node = init_word_redir_node(wr_node);
			// args = fill_redir_args(_head->content, _head->id);
			wr_node->type = _head->id;
			wr_node->file = ft_strdup(_head->next->content);
			_head = _head->next;
		}
		else if (_head && _head->id == TOK_PIPE)
		{
			// start building the next command in the pipeline
			*pipeline_cmd_tail = (*cmd)->next;
		}
		else if (_head && _head->id == TOK_ERRQUOTE)
		{
			exit (0);
		}
		_head = _head->next;
	}
	// if (wr_node)
	// {
	// 	printf("11\n");
	// 	(*cmd)->cmd_redir_node = add_redir_to_list(&(*cmd)->cmd_redir, wr_node);
	// 	wr_node = NULL;
	// }
	if (!*pipeline_head)
	{
		(*pipeline_head)->pipeline_node = *cmd;
		*pipeline_cmd_tail = *cmd;
	}
	else
	{
		(*pipeline_head)->pipeline_node = *cmd;
		*pipeline_cmd_tail = (*pipeline_cmd_tail)->next;
	}
}

void	*parse(t_token **token_head)
{
	t_cmd		*cmd;
	t_pipeline	*pipeline_head;
	t_cmd		**pipeline_cmd_tail;
	t_token		*token_temp; 
	
	cmd = NULL;
	pipeline_head = NULL;
	pipeline_cmd_tail = NULL;
	token_temp = *token_head; //preserve the head of token
	pipeline_cmd_tail = &cmd;
	while (token_temp)
	{
		if ((t_toktype)(token_temp->id) != TOK_PIPE)
		{
			// *pipeline_cmd_tail = init_cmd(); //init cmd at the head of the pipeline_list
			eval_token(token_temp, pipeline_cmd_tail, &pipeline_head, pipeline_cmd_tail); //token_temp->next
			printf("returned from eval_token OK\n");
			token_temp = token_temp->next;
		}
		else
		{
			//// skip over the pipeline delimiter token and move on to the next command
			// eval_token(token_temp, &cmd, &pipeline_head, pipeline_cmd_tail);
			token_temp = token_temp->next;
			pipeline_cmd_tail = &(*pipeline_cmd_tail)->next;
		}	
	}
	execute(pipeline_head);
	return (0);
}

// void	eval_token(t_token *token, t_cmd **cmd_tail, t_pipeline **pipeline_head, t_cmd ***pipeline_cmd_tail)
// {
// 	if (token && token->id == TOK_WORD)
// 	{
// 		append_arg(*cmd_tail, token->str);
// 	}
// 	else if (token && token->id == TOK_REDIRECT)
// 	{
// 		// handle input/output redirection
// 		...
// 	}
// 	else if (token && token->id == TOK_PIPE)
// 	{
// 		// start building the next command in the pipeline
// 		*pipeline_cmd_tail = &(*cmd_tail)->next;
// 	}
// 	else
// 	{
// 		// end of command, link it to the pipeline
// 		add_cmd_to_pipeline(*pipeline_cmd_tail, *pipeline_head);
// 		*cmd_tail = init_cmd();
// 	}
// }

// static t_redir_args *new_redir_args(char *content, t_toktype type)
// {
//     t_redir_args *new_args = NULL;
// 	new_args = init_args(new_args);
//     new_args->args = ft_strdup(content);
//     new_args->type = type;
//     new_args->next = NULL;
//     return (new_args);
// }