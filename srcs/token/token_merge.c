#include "../../headers/minishell.h"

void	*merge_tokens(t_token **token_head)
{
	// printf(GREEN "merge_tokens\n" RS);
	// print_token(*token_head);
	t_token	*curr;
	t_token	*temp = NULL;

	curr = *token_head;
	while (curr != NULL)
	{
		if (curr->next && (curr->id == TOK_WORD || curr->id == TOK_D_QUOTE || curr->id == TOK_S_QUOTE) &&
				(curr->next->id == TOK_WORD || curr->next->id == TOK_D_QUOTE || curr->next->id == TOK_S_QUOTE))
		{
			char *merged = ft_strjoin(curr->content, curr->next->content);
			if (!merged)
			{
				free_token_list(*token_head);
				return (NULL);
			}
			// printf(PURPLE "TOKEN before merge: %s=%d\n" RS, curr->content, curr->id);
			curr->content = merged;
			// printf(PURPLE "TOKEN after merge: %s=%d\n" RS, curr->content, curr->id);
			curr->id = TOK_WORD;
			if (curr->next)
			{
				// curr = curr->next;
				temp = curr->next;
				// my_free(curr->next);
				curr->next = temp->next;
				my_free(temp->content);
				my_free(temp);
			}			
		}
		else
			curr = curr->next;	
	}
	// printf("returning merged OK\n");
	return (NULL);
}
