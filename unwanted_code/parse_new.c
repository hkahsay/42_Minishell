
#include "minishell.h"

static t_cmd	*init_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd_args = NULL;
	new_cmd->cmd_redir = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

static t_redir_args	*init_redir_args(char *content, t_toktype type)
{
	t_redir_args *new_redir_args;

	new_redir_args = malloc(sizeof(t_redir_args));
	if (!new_redir_args)
		return (NULL);
	new_redir_args->type = type;
	new_redir_args->file = ft_strdup(content);
	new_redir_args->close_fd = 0;
	new_redir_args->next = NULL;
	return (new_redir_args);
}

static t_redir_args *add_redir_to_list(t_token **head, t_redir_args *redir_list)
{
	t_redir_args	*new_redir;
	t_redir_args	*current;

	new_redir = init_redir_args((*head)->next->content, (*head)->id);
	if (!new_redir)
		return (NULL);
	*head = (*head)->next;
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

static t_redir_args *add_args_to_list(t_redir_args **head_args, int type, char *content)
{
	t_redir_args *args = init_redir_args(content, type);

	if (!args)
		return (NULL);
	if (!*head_args)
		*head_args = args;
	else
	{
		t_redir_args *current = *head_args;
		while (current->next)
			current = current->next;
		current->next = args;
	}
	return (*head_args);
}

static void	eval_token(t_token *head, t_cmd **cmd, t_pipeline **pipeline_head, t_cmd **pipeline_tail)
{
	t_redir_args *args = NULL;

	*cmd = init_cmd();
	while (head && head->id != TOK_PIPE)
	{
		if (head->id == TOK_WORD || head->id == TOK_D_QUOTE || head->id == TOK_S_QUOTE)
		{
			while (head && (head->id == TOK_WORD || head->id == TOK_D_QUOTE || head->id == TOK_S_QUOTE))
			{
				if (head->id != TOK_D_QUOTE && head->id != TOK_S_QUOTE)
					(*cmd)->cmd_args = add_args_to_list(&args, head->id, head->content);
				if (head && (head->id == TOK_REDIR_IN || head->id == TOK_REDIR_OUT || head->id == TOK_REDIR_OUT_APPEND ||
							head->id == TOK_HEREDOC))
				{
					if (args)
					{
						(*cmd)->cmd_redir = add_redir_to_list(&head, (*cmd)->cmd_redir);
						args = NULL;
					}
					args = init_redir_args(head->next->content, head->id);
					head = head->next;
				}
				head = head->next;
			}
		}
		else if (head && (head->id == TOK_REDIR_IN


static void eval_token(t_token *head, t_cmd **cmd, t_pipeline **pipeline_head, t_cmd **pipeline_tail)
{
    t_redir_args *args = NULL;
    t_token *_head = NULL;
    *cmd = init_cmd();
    int i = 2;
    int j = 0;

    _head = head;
    while (_head && (t_toktype)(_head->id) != TOK_PIPE)
    {
        if (_head->id == TOK_WORD || _head->id == TOK_D_QUOTE || _head->id == TOK_S_QUOTE)
        {
            while (_head && (_head->id == TOK_WORD || _head->id == TOK_D_QUOTE || _head->id == TOK_S_QUOTE))
            {
                if (_head->id != TOK_D_QUOTE && _head->id != TOK_S_QUOTE)
                {
                    args = init_args(args);
                    args->type = _head->id;
                    args->file = ft_strdup(_head->content);
                    (*cmd)->cmd_args = add_args_to_list(&(*cmd)->cmd_args, args);
                    j++;
                }
                if (_head && (_head->id == TOK_REDIR_IN || _head->id == TOK_REDIR_OUT || _head->id == TOK_REDIR_OUT_APPEND || _head->id == TOK_HEREDOC))
                {
                    if (args)
                    {
                        (*cmd)->cmd_redir = add_redir_to_list(&(*cmd)->cmd_redir, args->type, args->file);
                        args = NULL;
                    }
                    args = init_args(args);
                    args->type = _head->id;
                    args->file = ft_strdup(_head->next->content);
                    _head = _head->next;
                }
                _head = _head->next;
            }
        }
        else if (_head && (_head->id == TOK_REDIR_IN || _head->id == TOK_REDIR_OUT || _head->id == TOK_REDIR_OUT_APPEND || _head->id == TOK_HEREDOC))
        {
            if (args)
            {
                (*cmd)->cmd_redir = add_redir_to_list(&(*cmd)->cmd_redir, args->type, args->file);
                args = NULL;
            }
            args = init_args(args);
            args->type = _head->id;
            args->file = ft_strdup(_head->next->content);
            _head = _head->next;
        }
        _head = _head->next;
    }
    if (args)
    {
        (*cmd)->cmd_redir = add_redir_to_list(&(*cmd)->cmd_redir, args->type, args->file);
        args = NULL;
    }
    if (!*pipeline_head)
    {
        *pipeline_head = *cmd;
        *pipeline_tail = *cmd;
    }
    else
    {
        (*pipeline_head) = *cmd;
        *pipeline_tail = (*pipeline_tail)->next;
    }
}
