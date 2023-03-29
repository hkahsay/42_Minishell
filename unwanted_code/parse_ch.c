#include "../../headers/minishell.h"

// typedef struct	s_cmd
// {
// 	t_arg			*cmd_args; // linked list of command arguments
// 	t_redir			*cmd_redir; // linked list of redirections
// 	struct s_cmd	*next; // pointer to the next command in a pipeline
// }	

// typedef struct	s_redir_args
// {
// 	t_toktype	type;
// 	char		*file;
// 	int			close_fd;
// 	struct s_redir_args *next;
// }				t_redir_args;

static t_redir_args	*init_args(t_redir_args *new_redir_args)
{
	new_redir_args = malloc(sizeof(t_redir_args) * 1);
	if (!new_redir_args)
		return (NULL);
	new_redir_args->type = 0;
	new_redir_args->args = NULL;
	return (new_redir_args);
}

static t_cmd	*init_cmd(void)
{
	t_cmd	*new_cmd;
	
	new_cmd = malloc(sizeof(t_cmd) * 1);
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd_args = NULL;
	new_cmd->cmd_redir = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

static t_redir_args *new_redir_args(char *content, t_toktype type)
{
    t_redir_args *new_args = NULL;
	new_args = init_args(new_args);
    new_args->args = ft_strdup(content);
    new_args->type = type;
    new_args->next = NULL;
    return (new_args);
}

t_redir_args	*add_redir_to_list(t_redir_args **head, t_toktype type, char *file)
{
	t_redir_args	*new_redir;
	t_redir_args	*current;

	new_redir = (t_redir_args *)malloc(sizeof(t_redir_args));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->file = file;
	new_redir->close_fd = 0;
	new_redir->next = NULL;
	if (!*head)
		*head = new_redir;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
	return (new_redir);
}

static void	eval_token(t_token *head, t_cmd **cmd, t_cmd **pipeline_head, t_cmd **pipeline_tail)
{
	t_redir_args *args = NULL;
	t_token *head_ptr = NULL;
	*cmd = init_cmd();
	int i = 2;
	int j = 0;

	head_ptr = head;
	while (head_ptr && (t_toktype)(head->id) != TOK_PIPE)
	{
		if (head_ptr->id == TOK_WORD || head_ptr->id == TOK_D_QUOTE || head_ptr->id == TOK_S_QUOTE)
		{
			while (head_ptr && (head_ptr->id == TOK_WORD || head_ptr->id == TOK_D_QUOTE || head_ptr->id == TOK_S_QUOTE))
			{
				if (head_ptr->id != TOK_D_QUOTE && head_ptr->id != TOK_S_QUOTE) // add valid tokens to cmd_args
				{
					(*cmd)->cmd_args = add_args_to_list(&args, head_ptr->id, head_ptr->content);
					while((*cmd)->cmd_args)
					{
						(*cmd)->cmd_args = (*cmd)->cmd_args->next;
						j++;
					}
				}
				if (head_ptr && (head_ptr->id == TOK_REDIR_IN || head_ptr->id == TOK_REDIR_OUT || head_ptr->id == TOK_REDIR_OUT_APPEND || head_ptr->id == TOK_HEREDOC))
				{
					if (args)
					{
						(*cmd)->cmd_redir = add_redir_to_list((*cmd)->cmd_redir, args);
						args = NULL;
					}
					args = init_redir_args(head_ptr->content, head_ptr->id);
				}
				head_ptr = head_ptr->next;
			}
		}
		else if (head_ptr->id == TOK_REDIR_IN || head_ptr->id == TOK_REDIR_OUT || head_ptr->id == TOK_REDIR_OUT_APPEND || head_ptr->id == TOK_HEREDOC)
		{
			if (args)
			{
				(*cmd)->cmd_redir = add_redir_to_list((*cmd)->cmd_redir, args);
				args = NULL;
			}
			args = init_redir_args(head_ptr->content, head_ptr->id);
			head_ptr = head_ptr->next;
		}
		else
			head_ptr = head_ptr->next;
	}
	if (args)
	{
		(*cmd)->cmd_redir = add_redir_to_list((*cmd)->cmd_redir, args);
		args = NULL;
	}
	if (!*pipeline_head)
	{
		*pipeline_head = *cmd;
		*pipeline_tail = *cmd;
	}
	else
	{
		(*pipeline_tail)->next = *cmd;
		*pipeline_tail = (*pipeline_tail)->next;
	}
}

t_cmd	*parse(t_token *head)
{
	t_cmd	*cmd = NULL;
	t_pipeline *pipeline_head = NULL;
	t_cmd	**pipeline_tail = &cmd;
	t_token *temp = head;
	
	while (temp)
	{
		if ((t_toktype)(temp->id) == TOK_PIPE)
		{
			*pipeline_tail = init_cmd();
			eval_token(temp->next, pipeline_tail, &pipeline_head, &pipeline_tail);
			temp = (*pipeline_tail)->next;
			continue;
		}
		eval_token(temp, &cmd, &pipeline_head, pipeline_tail);
		temp = temp->next;
	}
	execute(pipeline_head);
	return (pipeline_head);
}



/*
typedef struct	s_redir_args
{
	t_toktype	type;
	char		*file;
	int			close_fd;
	struct s_redir_args *next;
}				t_redir_args;

typedef struct	s_token
{
	int				id;
	char			*content;
	struct s_token	*next;
}				t_token;

typedef struct	s_redir_args
{
	int				type;
	char			*file;
	struct s_redir_args	*next;
}				t_redir_args;

typedef struct	s_cmd
{
	char			**cmd_args;
	t_redir_args	*cmd_redir;
	struct s_cmd	*next;
}				t_cmd;

static t_redir_args	*init_args(t_redir_args *new_redir_args)
{
	new_redir_args = malloc(sizeof(t_redir_args) * 1);
	if (!new_redir_args)
		return (NULL);
	new_redir_args->type = 0;
	new_redir_args->args = NULL;
	return (new_redir_args);
}

static t_cmd	*init_cmd(void)
{
	t_cmd	*new_cmd;
	
	new_cmd = malloc(sizeof(t_cmd) * 1);
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd_args = NULL;
	new_cmd->cmd_redir = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

static t_redir_args *new_redir_args(char *content, t_toktype type)
{
    t_redir_args *new_args = NULL;
	new_args = init_args(new_args);
    new_args->args = ft_strdup(content);
    new_args->type = type;
    new_args->next = NULL;
    return (new_args);
}

void print_t_redir_args(t_redir_args *temp)
{
	int i = 0;

	while (temp)
	{
		temp = temp->next;
		i++;
	}
}

static t_redir_args *add_args_to_list(t_redir_args **head_args, int type, char *content)
{
	t_redir_args *temp = NULL;

   
    t_redir_args *args = new_redir_args(content, type);

    if (*head_args == NULL)
    {
        *head_args = args;
    }
    else
    {
        t_redir_args *current = *head_args;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = args;
    }
	temp = *head_args;
	print_t_redir_args(temp);
	return (*head_args);
}

t_redir_args	*add_redir_to_list(t_redir_args **head, t_toktype type, char *file)
{
	t_redir_args	*new_redir;
	t_redir_args	*current;

	new_redir = (t_redir_args *)malloc(sizeof(t_redir_args));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->file = file;
	new_redir->close_fd = 0;
	new_redir->next = NULL;
	if (!*head)
		*head = new_redir;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
	return (new_redir);
}

static void	eval_token(t_token *head, t_cmd **cmd, t_cmd **pipeline_head, t_cmd **pipeline_tail)
{
	t_redir_args *redir_args = NULL;
	t_token *head_ptr = head;
	*cmd = init_cmd();
	int arg_count = 0;
	
	while (head_ptr && (t_toktype)(head_ptr->id) != TOK_PIPE)
	{
		if (head_ptr->id == TOK_WORD || head_ptr->id == TOK_D_QUOTE || head_ptr->id == TOK_S_QUOTE)
		{
			// Add argument to command
			(*cmd)->cmd_args = add_arg_to_list((*cmd)->cmd_args, head_ptr->id, head_ptr->content);
			arg_count++;
			
			// Check if the argument is followed by a redirection
			if (head_ptr->next && (head_ptr->next->id == TOK_REDIR_IN || head_ptr->next->id == TOK_REDIR_OUT ||
				head_ptr->next->id == TOK_REDIR_OUT_APPEND || head_ptr->next->id == TOK_HEREDOC))
			{
				// Add the redirection to the command
				head_ptr = head_ptr->next;
				redir_args = add_redir_arg_to_list(redir_args, head_ptr->id, head_ptr->content);
			}
		}
		else if (head_ptr->id == TOK_REDIR_IN || head_ptr->id == TOK_REDIR_OUT || head_ptr->id == TOK_REDIR_OUT_APPEND ||
			head_ptr->id == TOK_HEREDOC)
		{
			// Add the redirection to the command
			redir_args = add_redir_arg_to_list(redir_args, head_ptr->id, head_ptr->content);
		}
		else if (head_ptr->id == TOK_ENV_VAR)
		{
			// Expand the environment variable and add the expanded value to the command
			char *expanded = expand_env_var(head_ptr->content);
			(*cmd)->cmd_args = add_arg_to_list((*cmd)->cmd_args, TOK_WORD, expanded);
			free(expanded);
			arg_count++;
		}
		head_ptr = head_ptr->next;
	}

	// Set the number of arguments in the command
	(*cmd)->argc = arg_count;

	// Set the redirections for the command
	(*cmd)->redir_args = redir_args;

	if (!*pipeline_head)
	{
		// The current command is the first command in the pipeline
		*pipeline_head = *cmd;
	}
	else
	{
		// Add the current command to the pipeline
		(*pipeline_tail)->next = *cmd;
	}
	// Update the tail of the pipeline
	*pipeline_tail = *cmd;
}
*/