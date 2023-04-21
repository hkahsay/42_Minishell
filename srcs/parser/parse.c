#include "../../headers/minishell.h"

static t_cmd	*parse_commands(t_token **tok_head, int	cmd_num)
{
	t_token	*tok_h;
	t_token **tok_cmd_list;
	t_cmd	*cmd_list;
	int	i;

	tok_h = *tok_head;
	i = 0;
	// print_token(*tok_head);
	tok_cmd_list = my_malloc(sizeof(t_token *) * (cmd_num + 1));
	if (!tok_cmd_list)
		return (0);
	tok_cmd_list[cmd_num] = 0;
	// printf("tok_cmd_list %p\n", tok_cmd_list);
	while (tok_h && i < cmd_num)
	{
		tok_cmd_list[i] = tok_h;
		while (tok_h->next && tok_h->id != TOK_PIPE)
		{
			// printf(R "NO PIPE: " RS);
			// printf(R "%s\n" RS, tok_h->content);
			tok_h = tok_h->next;
			if (tok_h->id == TOK_PIPE)
				break ;
		}
		if (tok_h->id == TOK_PIPE)
			tok_h = tok_h->next;			
		i++;
	}
	// printf("NBR of cmds in cmd_list: %d\n", i);
	// print_tok_cmd_list(tok_cmd_list);
	cmd_list = build_cmd_list(tok_cmd_list);
	my_free(tok_cmd_list);
	return (cmd_list);
}

void	*parse(t_token **token_head, t_envnode *mini_env)
{
	int	list_size;
	int	cmd_num;
	t_cmd *cmd_list;

	list_size = ft_token_list_size(token_head);
	// printf("list_size %d\n", list_size);
	cmd_num = ft_count_pipes(token_head) + 1;
	// printf("cmd_index %d\n", cmd_num);
	cmd_list = parse_commands(token_head, cmd_num);
	free_token_list(*token_head);
	execute(cmd_list, cmd_num, mini_env);
	return (0);
}
