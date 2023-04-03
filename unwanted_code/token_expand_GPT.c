#include "../../headers/minishell.h"

// static int	mini_getenv(char *var_name, t_envnode *mini_env)
// {

// }

// int	get_$wordlen(char *s)
// {
// 	while (s && *s)
// 	{
// 		if 
// 	}
// }

static char	*expand_token(char *content, t_envnode *mini_env)
{
	print_mini_envp(mini_env);
	printf(R "expand_token function\n" RS);
	
	char *p;
	char	*dollar = NULL;
	char	*exp_content;	
	int		var_len;
	unsigned int		prefix_len;
	unsigned int		suffix_len;
	char	*var_name;
	char	*var_value;
	char	*temp_content;
	char	*prefix = NULL;
	// char	*suffix = NULL;
	p = content;
	char *s = content;
	char *r = NULL;
	while (p && *p)
	{
		s = NULL;
		if (!ft_strchr(content, '$')) //returns the char
			p++;
		// dollar = ft_strchr(content, '$'); //returns position of char if its found
		// printf("dollar: %s\n", dollar);

		// prefix = ft_substr(p, 0, ft_strcspn(p, "$")); //get_$wordlen(p)) " $;|&><\n" //
		// // *prefix = *content - *dollar;
		// p = p + ft_strcspn(p, "$");
		// printf("prefix: %s\n", prefix);
		// // s = s + ft_strcspn(p, "$");
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
			dollar = ft_substr(s + 1, 0, var_len); //char	*ft_substr(char const *s, unsigned int start, size_t len)
			printf("dollar: %s\n", dollar);
			p = p + var_len + 1;
			printf(GREEN "*p: %c\n" RS, *p);
			var_name = getenv(dollar);
			printf("var_name: %s\n", var_name);
			r = ft_strjoin(prefix, var_name);
			// free(prefix);
			printf("r: %s\n", r);
			s = ft_strjoin(r, p);
			printf("s: %s\n", s);
			// s = s + ft_strlen(r);
			// printf("*s: %c\n", *s);
			// suffix = ft_substr(r, 0, ft_strcspn(r, "$\0"));
			
			// printf("suffix: %s\n", suffix);
			// // s = s + ft_strlen(prefix) + ft_strlen(var_name) + 1;
			// printf("*s: %s\n", s);
			// printf("*s: %c\n", *s);
			p = s;
			// // p = 
			// sleep(100000);
		}
		if (*p && !ft_strchr(content, '$'))
			p++;
	}
	sleep(100000);
	// exp_content = ft_strdup(content);
	// dollar = ft_strchr(content, '$');
	// if (dollar == NULL)
	// 	return (strdup(content)); //nothing to expand

	while (dollar != NULL)
	{
		printf("1ex\n");
		// get the length of the variable name
		var_len = ft_strcspn(dollar + 1, " $;|&><\n");
		printf("var_len: %d\n", var_len);
		// copy the prefix of the token up to the dollar sign
		// var_name = &var_name[var_name_len + 1];
		char *prefix_name = ft_substr(content, 0, var_len);
		printf("prefix_name: %s\n", prefix_name);
		// var_name = 
		var_name = malloc(sizeof(char) * (var_len + 1));
		if (!var_name)
			return (NULL);
		
		printf("2ex\n");
		ft_strncpy(var_name, dollar + 1, (var_len + 1));
		printf("3ex\n");
		var_name[var_len] = '\0';
		printf("4ex\n");
		printf("var_name: %s\n", var_name);
		var_value = getenv(var_name); //mini_ , mini_env
		// replace the variable with its value, if it exists
		printf("var_value: %s\n", var_value);
		if (var_value != NULL)
		{
			prefix_len = dollar - exp_content;
			printf("prefix_len: %d\n", prefix_len);
			suffix_len = ft_strlen(dollar + var_len + 1);
			printf("suffix_len: %d\n", suffix_len);
			temp_content = malloc(sizeof(char) * (prefix_len + ft_strlen(var_value) + suffix_len + 1));
			if (temp_content == NULL)
			{
				free(exp_content);
				return (NULL);
			}
			// copy the prefix of the token up to the dollar sign
			ft_strncpy(temp_content, exp_content, prefix_len);
			temp_content[prefix_len] = '\0';
			// copy the value of the variable
			ft_strjoin(temp_content, var_value);
			// copy the rest of the token
			ft_strjoin(temp_content, dollar + var_len + 1);
			// replace the original token with the expanded one
			free(exp_content);
			exp_content = temp_content;
			dollar = ft_strchr(exp_content, '$');
		}
		else if (!var_value)
			ft_strlcat(exp_content, "", 1);
		else	
			dollar = ft_strchr(temp_content, '$');
	}
	printf(BLUE "temp_content: %s\n", temp_content);
	return (temp_content); 
}

t_token    *expand_token_list(t_token *token_head, t_envnode *mini_env)
{
	printf(R "expand_token_list function\n" RS);
	print_token(token_head);
	print_mini_envp(mini_env);

	t_token *exp_token_head;
	t_token	*exp_token_tail;
	t_token	*curr;
	char	*exp_content;

	exp_token_head = NULL;
	exp_token_tail = NULL;

	curr = token_head;
	printf(GREEN "expand_token_list 1\n" RS);
	while (curr != NULL)
	{
		printf(GREEN "expand_token_list 2\n" RS);
		printf(MAR "TOKEN: %s=%d\n" RS, curr->content, curr->id);
		if (curr->id == TOK_WORD || curr->id == TOK_D_QUOTE)
		{
			printf(GREEN "expand_token_list 3\n" RS);
			exp_content = expand_token(curr->content, mini_env);
			if (exp_content == NULL)
				return (NULL);
			//new content has to be rewritten into the token
		}
		curr = curr->next;
	}
	print_token(exp_token_head);
	return (exp_token_head);
}