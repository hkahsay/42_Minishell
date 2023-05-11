#include "../../headers/minishell.h"

void	*merge_tokens(t_token **token_head)
{
	t_token	*curr;
	t_token	*temp;
	char	*merged;

	curr = NULL;
	curr = *token_head;
	while (curr != NULL)
	{
		if (curr->next && (curr->id == TOK_WORD \
		|| curr->id == TOK_D_QUOTE || curr->id == TOK_S_QUOTE) \
		&& (curr->next->id == TOK_WORD || curr->next->id \
		== TOK_D_QUOTE || curr->next->id == TOK_S_QUOTE))
		{
			merged = ft_strjoin(curr->content, curr->next->content);
			if (!merged)
				return (NULL);
			curr->content = merged;
			curr->id = TOK_WORD;
			if (curr->next)
			{
				temp = curr->next;
				curr->next = temp->next;
				my_free(temp->content);
				my_free(temp);
			}			
		}
		else
			curr = curr->next;
	}
	return (NULL);
}
