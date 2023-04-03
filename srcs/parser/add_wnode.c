#include "../../headers/minishell.h"

// static int	is_dollar(char c)
// {
// 	if (c == '$')
// 		return (1);
// 	return (0);
// }

// static int	get_d_quote_wordlen(char *p)
// {
// 	int	len;
	
// 	len = 0;
// 	while (p && *p) //important order
// 	{
// 		if (is_dollar(*p) || ft_isspace(*p))
// 			return (len);
// 		len++;
// 		p++;
// 	}
// 	return (len);
// }

// static void	*expand_content_token(t_token **head, char *$content)
// {
// 	char	*p;

// 	p = $content;
// 	printf(OR "Ready to expand:" RS);
// 	print_token(*head);
// 	printf(R "Ready to expand content: %s\n" RS, $content);

// 	while (p && *p)
// 	{
// 		if (ft_isspace(*p))
// 			p++;
// 		if (is_dollar(*p) && *(p + 1))
// 		{
// 			while (!is_dollar(*p + 1) && !ft_isspace(*p + 1))
// 				p++;
// 			// get_$_value(ft_substr($content, 0, get_d_quote_wordlen(p)))	
// 		}
// 	}
// 	return (0);
// }

// static void	*eval_d_quote_token(t_token **head, char *t_quote)
// {
// 	char	*p;
// 	char	*dollar;

// 	p = t_quote;
// 	dollar = "$";
// 	while (p && *p)
//     {
// 		printf(BLUE "$ content: %c\n" RS, *p);	
// 		printf("1$\n");
// 		if (!is_dollar(*p))
// 			p++;
// 		if (!*p)
// 			break;
// 		if (is_dollar(*p) && *(p + 1) && !is_dollar(*p + 1) && !ft_isspace(*p + 1))
// 		{
// 			// if (!is_dollar(*p) && !ft_isspace(*p))
// 			printf("2$\n");
// 			expand_content_token(head, ft_substr(p, 0, get_d_quote_wordlen(p)));
// 			// p = p + get_wordlen(p);
// 			// continue;
// 		}
// 		p++;
		
// 	}
// 	return (head);			
// }

// char *check_$(char *word)
// {
// 	char *dollar_sign;

// 	dollar_sign = ft_strchr(word, '$');
//     if (dollar_sign != NULL) {
//         // Split the token into three parts
//         int prefix_len = dollar_sign - word;
//         char* var_name_start = dollar_sign;
//         int suffix_len = ft_strlen(dollar_sign) - 1;

//         char* prefix = strndup(word, prefix_len);
//         char* var_name = strndup(var_name_start, 2);
//         char* suffix = strndup(var_name_start + 2, suffix_len);

//         // Look up the value of the variable in the environment
//         char* var_value = getenv(var_name);

//         // Create a new list of tokens with the expanded variable
//         char** expanded_tokens = malloc(3 * sizeof(char*));
//         expanded_tokens[0] = prefix;
//         expanded_tokens[1] = var_value;
//         expanded_tokens[2] = suffix;

//         // Replace the original token in the list of tokens
//         free(tokens[i]);
//         tokens[i] = expanded_tokens;
//     }
// }

t_wr_node	*check_$_add_w_to_cmd_wnode(t_token **head, t_cmd **cmd, t_wr_node **head_wnode, int id, char *word, t_envnode *mini_env)
{
	t_wr_node	*new_wnode = NULL;
	t_wr_node	*temp = NULL;
	char		*d_quote = "\"";
	char		*t_quote;
	t_token *new_exp_token = NULL;
	t_token *exp_token_head = *head;

	print_cmd(*cmd);
	new_wnode = init_wr_node(new_wnode);
	if (id == TOK_D_QUOTE)
	{
		t_quote = ft_strtrim(word, d_quote);
		printf(R "Trimmed d_quote: %s\n" RS, t_quote);
		new_exp_token = expand_token_list(exp_token_head, mini_env);
		new_wnode = fill_wr_node(&new_wnode, new_exp_token->id, new_exp_token->content);
	}
		// new_wnode = fill_wr_node(&new_wnode, id, ft_strtrim(check_$(word), s_quote));
	if (id == TOK_WORD)
	{
		new_exp_token = expand_token_list(exp_token_head, mini_env);
		printf(BLUE "rentree, new_exp_token head:\n");
		print_token(new_exp_token);
		new_wnode = fill_wr_node(&new_wnode, new_exp_token->id, new_exp_token->content); //check_$(

	}
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

t_wr_node	*add_w_to_cmd_wnode(t_token **head, t_cmd **cmd, t_wr_node **head_wnode, int id, char *word)
{
	// print_wr_node(*cmd); 
	print_cmd(*cmd);
	print_token(*head);
	printf(MAGENTA "add_w_to_cmd_wnode received: %s %d\n" RS, word, id);

	t_wr_node	*new_wnode = NULL;
	t_wr_node	*temp = NULL;
	char		*s_quote = "\'";
	// while (*head && **head)
	

	new_wnode = init_wr_node(new_wnode);
	if (id == TOK_WORD)
	{
		
		// check_dollar(&(*head), cmd, &(*cmd)->cmd_wnode, (*head)->id, (*head)->content);
		new_wnode = fill_wr_node(&new_wnode, id, word);
	}
	if (id == TOK_S_QUOTE)
	{
		printf("S_QUOTE\n");
		new_wnode = fill_wr_node(&new_wnode, id, ft_strtrim(word, s_quote));
	}
	// if (id == TOK_D_QUOTE)
	// 	new_wnode = fill_wr_node(&new_wnode, id, ft_strtrim(word, s_quote));
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
