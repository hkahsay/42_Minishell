#include "../../headers/minishell.h"

t_wr_node	*check_dollar (t_token **head, t_cmd **cmd, t_wr_node **head_wnode, int id, char *word)
(
	t_wr_node	*new_wnode = NULL;
	t_wr_node	*temp = NULL;
	char		*s_quote = "\'";

	new_wnode = init_wr_node(new_wnode);
	return (*head_wnode);
)

t_wr_node	*add_w_to_cmd_wnode(t_token **head, t_cmd **cmd, t_wr_node **head_wnode, int id, char *word)
{
	// print_wr_node(*cmd); 
	print_cmd(*cmd);
	print_token(*head);
	printf(MAGENTA "add_w_to_cmd_wnode received: %s %d\n" RS, word, id);

	t_wr_node	*new_wnode = NULL;
	t_wr_node	*temp = NULL;
	char		*s_quote = "\'";

	new_wnode = init_wr_node(new_wnode);
	if (id == TOK_WORD)
	{
		check_dollar(&(*head), cmd, &(*cmd)->cmd_wnode, (*head)->id, (*head)->content);
		//new_wnode = fill_wr_node(&new_wnode, id, word);
	}
	if (id == TOK_S_QUOTE)
		new_wnode = fill_wr_node(&new_wnode, id, ft_strtrim(word, s_quote));
	if (!new_wnode)
		return (NULL);
	if (*head_wnode == NULL)
		*head_wnode = new_wnode;
	else
	{
		temp = *head_wnode;
		while (temp->next)
			temp = temp->next;	
		temp->next = new_wnode;
	}
	return (*head_wnode);
}
