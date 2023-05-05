#include "../../headers/minishell.h"

static int	ft_red_list_size(t_token **ptr_cmd_red)
{
	t_token *red;
	int		size;

	red = *ptr_cmd_red;
	size = 0;
	while (red != NULL)
	{
		if (red != NULL && (red->id == TOK_REDIR_IN || red->id == TOK_REDIR_OUT || red->id == TOK_REDIR_OUT_APPEND || red->id == TOK_HEREDOC))
			size++;
		red = red->next;
	}
	return (size);
}

int	ft_handle_redir_all(t_ppline **new_ppline, t_token *ptr_cmd_red)
{
	printf(GOLD "Redir_all\n" RS);
	// (void)new_ppline;
	t_token *red_ptr;
	// (void)ptr_cmd_red;
	red_ptr = ptr_cmd_red;


	//count redir list size and make an array of redir
	//check permissions of opened files
	int	red_list_size = ft_red_list_size(&red_ptr);
	(*new_ppline)->ppline_red = (char **)malloc(sizeof(char *) * (red_list_size + 1));
	if ((*new_ppline)->ppline_red == NULL)
	{
		free(new_ppline);
		return NULL;
	}
	printf(GOLD "Redir_list size: %d\n" RS, red_list_size);
	if (red_ptr->id == TOK_REDIR_OUT)
	{
		printf(GOLD "Redir_out\n" RS);
		ft_handle_redir_out(new_ppline, &ptr_cmd_red);
		return (1);
	}
	if (red_ptr->id == TOK_REDIR_OUT_APPEND)
	{
		printf(GOLD "Redir_out_append\n" RS);
		ft_handle_redir_append(new_ppline, &ptr_cmd_red);
		return (1);
	}
	if (red_ptr->id == TOK_REDIR_IN)
	{
		printf(GOLD "Redir_in\n" RS);
		ft_handle_redir_in(new_ppline, &ptr_cmd_red);
		return (1);
	}
	if (red_ptr->id == TOK_HEREDOC)
	{
		printf(GOLD "Redir_all\n" RS);
		(*new_ppline)->pp_heredoc_status = 1;
		ft_handle_heredoc(new_ppline, &ptr_cmd_red);	

		return (1);
	}
	return (1);
}
