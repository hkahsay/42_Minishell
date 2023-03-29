t_cmd *create_new_cmd() {
    t_cmd *new_cmd = (t_cmd*) malloc(sizeof(t_cmd));
    new_cmd->cmd_args = NULL;
    new_cmd->cmd_redir = NULL;
    return new_cmd;
}

t_redir_args *create_new_arg(t_toktype type, char *content) {
    t_redir_args *new_arg = (t_redir_args*) malloc(sizeof(t_redir_args));
    new_arg->type = type;
    new_arg->args = content;
    new_arg->next = NULL;
    return new_arg;
}

void add_arg_to_cmd(t_cmd *cmd, t_redir_args *arg) {
    if (cmd->cmd_args == NULL) {
        cmd->cmd_args = arg;
    } else {
        t_redir_args *last_arg = cmd->cmd_args;
        while (last_arg->next != NULL) {
            last_arg = last_arg->next;
        }
        last_arg->next = arg;
    }
}

void add_cmd_to_pipeline(t_cmd *cmd, t_pipeline **pipeline) {
    if (*pipeline == NULL) {
        // this is the first command in the pipeline
        t_pipeline *new_pipeline = (t_pipeline*) malloc(sizeof(t_pipeline));
        new_pipeline->cmd_index = 1;
        new_pipeline->cmd_node = cmd;
        *pipeline = new_pipeline;
    } else {
        // add the new command to the existing pipeline
        int new_cmd_index = (*pipeline)->cmd_index + 1;
        t_pipeline *new_pipeline = (t_pipeline*) malloc(sizeof(t_pipeline));
        new_pipeline->cmd_index = new_cmd_index;
        new_pipeline->cmd_node = cmd;
        (*pipeline)->next = new_pipeline;
        *pipeline = new_pipeline;
    }
}

t_pipeline *split_tokens_into_pipeline(t_token *tokens) {
    t_pipeline *first_pipeline = NULL;
    t_pipeline *current_pipeline = NULL;
    t_cmd *current_cmd = NULL;
    t_redir_args *current_arg = NULL;
    t_toktype current_toktype = TOK_ERROR;

    // iterate through the token list
    t_token *current_token = tokens;
    while (current_token != NULL) {
        // get the token type
        t_toktype toktype = current_token->id;

        // update the current command and pipeline based on the token type
        if (toktype == TOK_WORD) {
            if (current_toktype != TOK_WORD) {
                // start a new command
                current_cmd = create_new_cmd();
                add_cmd_to_pipeline(current_cmd, &current_pipeline);
            }

            // add the token to the current command's argument list
            t_redir_args *new_arg = create_new_arg(TOK_WORD, current_token->content);
            add_arg_to_cmd(current_cmd, new_arg);
            current_arg = new_arg;
        } else if (toktype == TOK_REDIR_OUT || toktype == TOK_REDIR_IN || toktype == TOK_REDIR_OUT_APPEND) {
            // start a new command if the previous token was not a redirection
            if (current_toktype != TOK_REDIR_OUT && current_toktype != TOK_REDIR_IN && current_toktype != TOK_REDIR_OUT_APPEND) {
                current_cmd = create_new_cmd();
                add_cmd_to_pipeline(current_cmd, &current_pipeline);
            }

            // add the redirection to the current command's redirection list
            t_redir_args *new_redir = create_new_arg(toktype, current_token->content);
            if (current_cmd->cmd_redir == NULL) {
                current_cmd->cmd_redir