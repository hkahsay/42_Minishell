#include "../../headers/minishell.h"

t_wr_node	*fill_wr_node(t_wr_node **wr_node, int id, char *word)
{
	(*wr_node)->type = id;
	(*wr_node)->file = word;
	(*wr_node)->close_fd = 0;
	(*wr_node)->next = NULL;
	printf(GREEN "init: new_wr_node content %p %s %d\n" RS, (*wr_node)->file, (*wr_node)->file, (*wr_node)->type);
	return (*wr_node);
}

// static int	get_q_wordlen(char *p)
// {
// 	int	len;
	
// 	len = 0;
// 	while (p && *p) //important order
// 	{
// 		if (ft_isspace(*p))
// 			return (len);
// 		len++;
// 		p++;
// 	}
// 	// printf("len: %d\n", len);
// 	return (len);
// }


// static void	*interpret_dollar(t_token **head, char **clean_word)
// {
// 	t_token	*token = NULL;
// 	char	*p;

// 	while (*clean_word && **clean_word)
// 	{
// 		p = *clean_word;
// 		printf("*clean_word: %s\n", *clean_word);
// 		if (p && *p && *p != '$')
// 		{
// 			p = *clean_word;
// 			while (p && *p && *p != '$')
// 			{
// 				printf("*p: %c\n", *p);
// 				p++;
// 			}
// 			token = init_token(token);
// 			printf("*p: %c\n", *p);
// 			int len = p - *clean_word;
// 			printf("len: %d\n", len);
// 			add_token(head, ft_substr(p, 0, len), TOK_WORD);
// 			print_token(token);
// 			sleep(100000);
// 		}	
// 			if (*p == '$')
// 			{
// 				p = *clean_word;
// 				if (*p == '\0' || *p ==  ' ' || **clean_word == '\t' || *p == '\n')
// 				{
// 					add_token(head, ft_substr(p, 0, get_q_wordlen(p)), TOK_WORD);
// 					printf("token added\n");
// 					p = p + get_wordlen(p);
// 				}
// 				p++;
// 			}
			
// 	}
// 	return (0);
// }

// static t_token	*expand_d_quote(t_token **head, char *word) // t_cmd **cmd, t_wr_node **head_wnode, int id, 
// {
// 	// print_wr_node(*cmd); 
// 	// print_cmd(*cmd);
// 	// print_token(*head);
// 	// printf(OR "expand_add_w_to_cmd_wnode received: %s %d\n" RS, word, id);

// 	// t_wr_node	*new_wnode = NULL;
// 	// t_wr_node	*temp = NULL;
// 	char		*s_quote = "\"";
// 	char 		*clean_word;
	
// 	clean_word = ft_strtrim(word, s_quote);
// 	printf("clean_word: %s\n", clean_word);
// 	// sleep(100000);
// 	interpret_dollar(head, &clean_word);
// 	return (*head);
// 	new_wnode = init_wr_node(new_wnode);
// 	if (id == TOK_D_QUOTE)
	
// 	dollar_split(clean_word);

// 	new_wnode = fill_wr_node(&new_wnode, id, ft_strtrim(word, s_quote));
	
// 	if (!new_wnode)
// 		return (NULL);
// 	if (*head_wnode == NULL)
// 		*head_wnode = new_wnode;
// 	else
// 	{
// 		temp = *head_wnode;
// 		while (temp->next)
// 			temp = temp->next;	
// 		temp->next = new_wnode;
// 	}
// 	return (*head_wnode);
// }

static void	eval_token(t_token **tok_head, t_cmd **cmd, t_cmd **cmd_pline_tail, t_envnode *mini_env)
{
	printf("1\n");
	printf("TOK_WORD %p %s %d\n", (*tok_head)->content, (*tok_head)->content, (*tok_head)->id);
	print_cmd(*cmd);
	print_cmd(*cmd_pline_tail);
	print_mini_envp(mini_env);

	t_wr_node	*wr_node = NULL;
	// t_token		*ptr_tok_head = NULL;

	wr_node = init_wr_node(wr_node);
	// tok_head = tok_head;
	while ((*tok_head) && (t_toktype)((*tok_head)->id) != TOK_PIPE)
	{
		if ((*tok_head)->id == TOK_WORD || (*tok_head)->id == TOK_S_QUOTE || (*tok_head)->id == TOK_D_QUOTE)
		{
			while ((*tok_head) && ((*tok_head)->id == TOK_WORD || (*tok_head)->id == TOK_D_QUOTE || (*tok_head)->id == TOK_S_QUOTE || (*tok_head)->id == TOK_SPACE))
			{
				if ((*tok_head)->id == TOK_WORD || (*tok_head)->id == TOK_D_QUOTE)
				{
					printf("4a\n");
					(*cmd)->cmd_wnode = check_$_add_w_to_cmd_wnode(&(*tok_head), cmd, &(*cmd)->cmd_wnode, (*tok_head)->id, (*tok_head)->content);
					// tok_head = tok_head->next;
					// *tok_head = (*tok_head)->next;
					printf(BLUE "rentree, new_token head:\n");
					print_token(*tok_head);
					print_cmd(*cmd);
					printf(RS);
				}
				else if ((*tok_head)->id == TOK_S_QUOTE)
				{
					printf("4b\n");
					(*cmd)->cmd_wnode = add_w_to_cmd_wnode(&(*tok_head), cmd, &(*cmd)->cmd_wnode, (*tok_head)->id, (*tok_head)->content);
				}
				// else if ((*tok_head)->id == TOK_D_QUOTE)
				// {
				// 	printf("4c\n");
				// 	*tok_head = expand_d_quote((tok_head), (*tok_head)->content); //cmd, &(*cmd)->cmd_wnode, (*tok_head)->id, 
				// 	(*cmd)->cmd_wnode = add_w_to_cmd_wnode(&(*tok_head), cmd, &(*cmd)->cmd_wnode, (*tok_head)->id, (*tok_head)->content);
				// 	// (*cmd)->cmd_wnode = expand_d_quote_add(&(*cmd)->cmd_wnode, tok_head->id, tok_head->content);
				// }
				else if (tok_head && ((*tok_head)->id == TOK_REDIR_IN || (*tok_head)->id == TOK_REDIR_OUT || (*tok_head)->id == TOK_REDIR_OUT_APPEND ||
					(*tok_head)->id == TOK_HEREDOC))
				{
					printf("4d\n");
					// (*cmd)->cmd_rnode = add_r_to_cmd_rnode(&(*cmd)->cmd_wnode, tok_head->id, tok_head->content);
				}
				printf("4e\n");
				*tok_head = (*tok_head)->next;
			}
		}
		else if (tok_head && ((*tok_head)->id == TOK_REDIR_IN || (*tok_head)->id == TOK_REDIR_OUT || (*tok_head)->id == TOK_REDIR_OUT_APPEND ||
					(*tok_head)->id == TOK_HEREDOC))
		{
			printf("5\n");
			// (*cmd)->cmd_rnode = add_r_to_cmd_rnode(&(*cmd)->cmd_wnode, tok_head->id, tok_head->content);
		}
		else if (tok_head && (*tok_head)->id == TOK_PIPE)
		{
			printf("6\n");
			*cmd_pline_tail = (*cmd)->next;
		}
	}
}

void	*parse(t_token **tok_head, t_envnode *mini_env)
{
	t_cmd	*cmd;
	t_token *tok_temp;
	t_cmd	**cmd_pline_tail;

	// cmd = init_cmd();
	tok_temp = NULL;
	// cmd_pline_tail = NULL;
	tok_temp = *tok_head; //preserve the head of token list to be able to free tok_list
	
	cmd_pline_tail = &cmd;
	printf("init cmd_pline_tail OK\n");
	while (tok_temp)
	{
		cmd = init_cmd();
		cmd_pline_tail = &cmd;
		if (tok_temp->id != TOK_PIPE)
		{
			
			eval_token(&tok_temp, &cmd, cmd_pline_tail, mini_env);
			printf(R "ok\n" RS);
			// tok_temp = tok_temp->next;
		}
		else
		{
			tok_temp = tok_temp->next;
			
			cmd_pline_tail = &(*cmd_pline_tail)->next;
			printf(GREEN "ok\n" RS);
		}
		// execute(cmd);
	}
	execute(cmd);
	return (0);
}