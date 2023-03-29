#include "../../headers/minishell.h"

static t_cmd *create_new_cmd(void)
{
    t_cmd *new_cmd = malloc(sizeof(t_cmd));
    new_cmd->cmd_args = NULL;
    new_cmd->cmd_redir = NULL;
    return new_cmd;
}

static t_redir_args *create_new_arg(t_toktype type, char *content)
{
    t_redir_args *new_arg = malloc(sizeof(t_redir_args));
    new_arg->type = type;
    new_arg->args = content;
    new_arg->next = NULL;
    return new_arg;
}

static void add_arg_to_cmd(t_cmd *cmd, t_redir_args *arg)
{
    if (cmd->cmd_args == NULL)
	{
        cmd->cmd_args = arg;
    }
	else
	{
        t_redir_args *current_arg = cmd->cmd_args;
        while (current_arg->next != NULL)
		{
            current_arg = current_arg->next;
        }
        current_arg->next = arg;
    }
}

static void add_redir_to_cmd(t_cmd *cmd, t_redir_args *redir)
{
    if (cmd->cmd_redir == NULL)
	{
        cmd->cmd_redir = redir;
    } else
	{
        t_redir_args *current_redir = cmd->cmd_redir;
        while (current_redir->next != NULL)
		{
            current_redir = current_redir->next;
        }
        current_redir->next = redir;
    }
}

static t_pipeline *create_new_pipeline(int index, t_cmd *cmd)
{
    t_pipeline *new_pipeline = malloc(sizeof(t_pipeline));
    new_pipeline->cmd_index = index;
    new_pipeline->cmd_node = cmd;
    return new_pipeline;
}

static void add_cmd_to_pipeline(t_cmd *cmd, t_pipeline **pipeline)
{
    if (*pipeline == NULL)
	{
        // create a new pipeline and add the current command to it
        *pipeline = create_new_pipeline(0, cmd);
    }
	else
	{
        // check if the current command should be added to the current pipeline
        t_pipeline *current_pipeline = *pipeline;
        t_cmd *last_cmd = current_pipeline->cmd_node;
        if (last_cmd->cmd_redir == NULL && cmd->cmd_redir == NULL)
		{
            // add the current command to the existing pipeline
            add_redir_to_cmd(last_cmd, cmd->cmd_args);
            free(cmd);
        }
		else
		{
            // create a new pipeline and add the current command to it
            int index = current_pipeline->cmd_index + 1;
            t_pipeline *new_pipeline = create_new_pipeline(index, cmd);
            current_pipeline->next = new_pipeline;
            *pipeline = new_pipeline;
        }
    }
}

t_cmd *split_tokens_into_cmds(t_token **tokens)
{
    t_cmd *first_cmd = NULL;
    t_cmd *current_cmd = NULL;
    t_redir_args *current_arg = NULL;

    // iterate through the token list
    t_token *current_token = *tokens;
    while (current_token != NULL)
	{
        // get the token type
        t_toktype toktype = current_token->id;

        // add the token to the current command's argument list
        if (toktype == TOK_WORD)
		{
            if (current_cmd == NULL)
			{
                // start a new command
                current_cmd = create_new_cmd();
                if (first_cmd == NULL)
				{
                    first_cmd = current_cmd;
                }
            }
            t_redir_args *new_arg = create_new_arg(TOK_WORD, current_token->content);
            add_arg_to_cmd(current_cmd, new_arg);
            current_arg = new_arg;
        }
		else if (toktype == TOK_REDIR_OUT || toktype == TOK_REDIR_IN || toktype == TOK_REDIR_OUT_APPEND)
		{
            // start a new command if the previous token was not a redirection
            if (current_arg == NULL || current_arg->type != toktype)
			{
                current_cmd = create_new_cmd();
                if (first_cmd == NULL)
				{
                    first_cmd = current_cmd;
                }
            }

            // add the redirection to the current command's redirection list
            t_redir_args *new_redir = create_new_arg(toktype, current_token->content);
            add_redir_to_cmd(current_cmd, new_redir);
            current_arg = new_redir;
        }

        // move on to the next token
        current_token = current_token->next;
    }

    // update the token list pointer to point to the next unparsed token
    *tokens = current_token;

    return first_cmd;
}

// t_cmd *split_tokens_into_cmds(t_token **tokens) {
//     t_cmd *first_cmd = NULL, *current_cmd = NULL;
//     t_redir_args *current_arg = NULL, *new_arg = NULL, *new_redir = NULL;
//     t_token *tok = *tokens;

//     while (tok) {
//         if (tok->id == TOK_WORD) {
//             if (!current_cmd) {
//                 current_cmd = create_new_cmd();
//                 first_cmd = current_cmd;
//             }
//             new_arg = create_new_arg(TOK_WORD, tok->content);
//             add_arg_to_cmd(current_cmd, new_arg);
//             current_arg = new_arg;
//         }
//         else if (tok->id == TOK_REDIR_OUT || tok->id == TOK_REDIR_IN || tok->id == TOK_REDIR_OUT_APPEND) {
//             if (!current_arg || current_arg->type != tok->id) {
//                 current_cmd = create_new_cmd();
//                 if (!first_cmd) first_cmd = current_cmd;
//             }
//             new_redir = create_new_arg(tok->id, tok->content);
//             add_redir_to_cmd(current_cmd, new_redir);
//             current_arg = new_redir;
//         }
//         tok = tok->next;
//     }
//     *tokens = tok;
//     return first_cmd;
// }

// t_cmd *split_tokens_into_cmds(t_token **tokens) {
//     t_cmd *first_cmd = NULL, *current_cmd = NULL;
//     t_redir_args *current_arg = NULL;
//     t_token *current_token = *tokens;

//     while (current_token) {
//         t_toktype toktype = current_token->id;
//         if (toktype == TOK_WORD) {
//             if (!current_cmd) first_cmd = current_cmd = create_new_cmd();
//             t_redir_args *new_arg = create_new_arg(TOK_WORD, current_token->content);
//             add_arg_to_cmd(current_cmd, (current_arg = new_arg));
//         }
//         else if (toktype == TOK_REDIR_OUT || toktype == TOK_REDIR_IN || toktype == TOK_REDIR_OUT_APPEND) {
//             if (!current_arg || current_arg->type != toktype) first_cmd = current_cmd = create_new_cmd();
//             t_redir_args *new_redir = create_new_arg(toktype, current_token->content);
//             add_redir_to_cmd(current_cmd, (current_arg = new_redir));
//         }
//         current_token = current_token->next;
//     }
//     *tokens = current_token;
//     return first_cmd;
// }

/*This function takes a pointer to a pointer to the head of the token list,
 and returns a pointer to the head of the resulting command list. 
 It works by iterating through the token list and adding each token to 
 the appropriate command's argument or redirection list, creating new commands as necessary. 
 It also updates the token list pointer to point to the next unparsed token.

split_tokens_into_cmds function will create several t_cmd linked lists, 
where each list represents a command with its arguments and redirections. 
The function will return the first t_cmd node of the first linked list, 
and it will modify the tokens argument to remove the tokens that were already processed into t_cmd nodes.

After calling split_tokens_into_cmds, you can iterate over the linked list of t_cmd nodes a
nd execute each command separately, or you can group multiple t_cmd nodes into a t_pipeline node 
to execute them together in a pipeline.




t_pipeline is not a linked list, but rather a single node that represents a pipeline. 
A pipeline is a sequence of one or more commands separated by pipe symbols (|).

The t_pipeline struct contains a cmd_index integer, which represents the position of the current command within the pipeline, 
and a cmd_node pointer, which points to the t_cmd node that represents the current command.

You can use a linked list of t_pipeline nodes to represent a list of pipelines, 
where each node in the linked list represents a pipeline. You can then execute each pipeline separately, 
or group multiple pipelines into a t_job node to execute them together in a job.
*/


