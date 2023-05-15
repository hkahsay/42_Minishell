#include "../../headers/minishell.h"

static void	assign_merged(t_token **temp, t_token **c)
{
	(*temp) = (*c)->next;
	(*c)->next = (*temp)->next;
	my_free((*temp)->content);
	my_free((*temp));
}

void	*merge_tokens(t_token **token_head)
{
	t_token	*c;
	t_token	*temp;
	char	*merged;

	c = NULL;
	c = *token_head;
	while (c != NULL)
	{
		if (c->next && (c->id == T_W || c->id == T_DQ || c->id == T_SQ) && \
		(c->next->id == T_W || c->next->id == T_DQ || c->next->id == T_SQ))
		{
			merged = ft_strjoin(c->content, c->next->content);
			if (!merged)
				return (NULL);
			c->content = merged;
			c->id = T_W;
			if (c->next)
				assign_merged(&temp, &c);
		}
		else
			c = c->next;
	}
	return (NULL);
}
