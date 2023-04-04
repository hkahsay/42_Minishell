#include "../../headers/minishell.h"

static char	*mini_getenv(char *var_name, int var_len, t_envnode *mini_env)
{
	t_envnode *mini_env_temp;

	mini_env_temp = mini_env;
	printf(R "HELLO mini_getenv\n");
	print_mini_envp(mini_env_temp);
	printf(BLUE "var_name in mini_getenv %s\n" RS, var_name);
	while(mini_env_temp)
	{
		printf(R "in while loop mini_getenv\n");
		if (ft_strncmp(var_name, mini_env_temp->key, var_len) == 0)
		{
			printf(GREEN "FOUND var_name %s mini_env->key %s mini_env->value: %s\n" RS, var_name, mini_env->key, mini_env->value);
			return (mini_env_temp->value);
		}
		mini_env_temp = mini_env_temp->next;
	}
	return (NULL);
}

static char	*expand_token(char **content, int id, t_envnode *mini_env) //t_token **curr, 
{
	// print_mini_envp(mini_env);
	printf(R "expand_token function *content: %s\n" RS, *content);
	// t_token *curr = init_token(curr);
	char *p;
	// char	*dollar = NULL;
	// char	*exp_content;	
	int		var_len;
	// unsigned int		prefix_len;
	// unsigned int		suffix_len;
	char	*var_name;
	char	*var_value;
	// char	*temp_content;
	char	*prefix = NULL;
	// char	*suffix = NULL;
	p = *content;
	char *s = NULL;
	char *r = NULL;
	printf("p: %s\n", p);
	if (id == TOK_WORD || id == TOK_D_QUOTE)
	{
		while (p && *p)
		{
			// s = p;
			if (!ft_strchr(p, '$')) //returns the char
				p++;
			if (!p[0])
			{
				return (*content);
			}
			// dollar = ft_strchr(content, '$'); //returns position of char if its found
			// printf("dollar: %s\n", dollar);

			// prefix = ft_substr(p, 0, ft_strcspn(p, "$")); //get_$wordlen(p)) " $;|&><\n" //
			// // *prefix = *content - *dollar;
			// p = p + ft_strcspn(p, "$");
			// printf("prefix: %s\n", prefix);
			// // s = s + ft_strcspn(p, "$");
			// p = s;
			if (ft_strchr(p, '$') && *(p + 1))
			{
				printf(R "1\n");

				prefix = ft_substr(p, 0, ft_strcspn(p, "$")); //get_$wordlen(p)) " $;|&><\n" //
				// *prefix = *content - *dollar;
				p = p + ft_strcspn(p, "$");
				printf("prefix: %s\n", prefix);
				// s = s + ft_strcspn(p, "$");
				printf("prefix: %s\n" RS, prefix);

				s = p;
				printf("*s: %c\n", *s);
				printf("*(s + 1): %c\n", *(s + 1));
				var_len = ft_strcspn(s + 1, " $;|&><\n");
				printf("var_len: %d\n", var_len);
				printf("*s: %c\n", *s);
				var_name = ft_substr(s + 1, 0, var_len); //char	*ft_substr(char const *s, unsigned int start, size_t len)
				printf("var_name: %s\n", var_name);
				p = p + var_len + 1;
				printf(GREEN "*p: %c\n" RS, *p);
				var_value = mini_getenv(var_name, var_len, mini_env);
				printf("var_name: %s\n", var_value);
				r = ft_strjoin(prefix, var_value);
				// free(prefix);
				printf("r: %s\n", r);
				s = ft_strjoin(r, p);
				printf("s: %s\n", s);
				// s = s + ft_strlen(r) + ft_strlen(p);
				// printf("*s: %c\n", *s);
				// suffix = ft_substr(r, 0, ft_strcspn(r, "$\0"));
				
				// printf("suffix: %s\n", suffix);
				// // s = s + ft_strlen(prefix) + ft_strlen(var_name) + 1;
				// printf("*s: %s\n", s);
				// printf("*s: %c\n", *s);
				// p = s;
				printf("p: %s\n", p);
				printf("*p: %c\n", *p);
				printf(R "2\n" RS);
				// if (!ft_strchr(p, '$')) //returns the char
				// 	p++;
				// if (!p)
				// 	break;// return (*content = ft_strdup(s));
				// // p = 
				// s = s + ft_strlen(r) + ft_strlen(p);
				printf("s after s + ft_strlen(r) + ft_strlen(p): %s\n", s);
				return (expand_token((&s), id, mini_env));
			}
		}

	}
	// free(content);
	// free((*curr)->content);
	// *content = ft_strdup(p);
	printf("p: %s\n", p);
	return (*content = ft_strdup(p)); 
}

t_token    *expand_token_list(t_token *token_head, t_envnode *mini_env)
{
	printf(R "expand_token_list function\n" RS);
	print_token(token_head);
	// print_mini_envp(mini_env);
	t_token *new_exp_token = NULL;
	t_token *exp_token_head;
	t_token	*exp_token_tail;
	t_token	*curr;
	char	*exp_content;
	char	*trimmed;
	char		*d_quote = "\"";

	exp_token_head = NULL;
	exp_token_tail = NULL;

	curr = token_head;
	init_token(new_exp_token);
	printf(GREEN "expand_token_list 1\n" RS);
	while (curr != NULL)
	{
		
		printf(GREEN "expand_token_list 2\n" RS);
		printf(MAR "TOKEN: %s=%d\n" RS, curr->content, curr->id);
		if (curr->id == TOK_WORD || curr->id == TOK_D_QUOTE)
		{
			if (curr->id == TOK_D_QUOTE)
			{
				trimmed = ft_strtrim(curr->content, d_quote);
				free(curr->content);
				curr->content = ft_strdup(trimmed);
				printf(OR "curr->content %s\n" RS, curr->content);
			}
			printf(GREEN "expand_token_list 3\n" RS);
			exp_content = expand_token(&curr->content, curr->id, mini_env); //&curr, 
			printf(R "RETURNED to exp_token_list content: %s => %s\n" RS, curr->content, exp_content);
			// sleep(100000);
			if (exp_content == NULL)
				return (NULL);
			if (curr->id == TOK_WORD)
			{
				int	i = 0;
				char **words = ft_split(exp_content, ' ');
				if (words != NULL)
				{
					while (words[i])
					{
						add_token(&exp_token_head, exp_content, TOK_WORD);
						// new_exp_token = new_token(words[i], TOK_WORD);
						if (new_exp_token == NULL)
							break;
						if(exp_token_head == NULL)
							exp_token_head = new_exp_token;
						else		
						{
							exp_token_tail = last_token(exp_token_head);
							exp_token_tail->next = new_exp_token;
						}
						i++;	
					}
					free(words);
				}
			}
			// new_exp_token = 
			// add_token(&exp_token_head, exp_content, TOK_WORD);
			//new content has to be rewritten into the token
		}
		// sleep(100000);
		// int	i = 0;
		// char **words = ft_split(exp_content, ' ');
		// if (words != NULL)
		// {
		// 	while (words[i])
		// 	{
		// 		new_exp_token = new_token(words[i], TOK_WORD);
		// 		if (new_exp_token == NULL)
		// 			break;
		// 		if(exp_token_head == NULL)
		// 			exp_token_head = new_exp_token;
		// 		else		
		// 		{
		// 			exp_token_tail = last_token(exp_token_head);
		// 			exp_token_tail->next = new_exp_token;
		// 		}
		// 		i++;	
		// 	}
		// 	free(words);
		// }
		curr = curr->next;
	}
	print_token(exp_token_head);
	return (exp_token_head);
}