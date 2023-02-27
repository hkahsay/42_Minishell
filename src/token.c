#include"../minishell.h"

//in token whe have the content and unique id for 
//very contents in every classes
t_list	*create_token(char *content, int id)
{
	t_list	*token;

	token = init_token();
	token->id_token = id;
	token->class = content;
	printf("content %s\n", token->class);
	return (0);
}

t_cmd	*create_cmd(char *content, pid_t id)
{
	t_cmd	*cmd;

	cmd = init_cmd();
	cmd->content = content;
	cmd->process_id = id;
	return (0);
}
