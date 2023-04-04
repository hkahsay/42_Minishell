#include"../../headers/minishell.h"

  // current directory environment variable

/* Helper function to find an environment variable by key */
t_envnode *find_env_var(char *key, t_envnode *current_dir)
{
    t_envnode *current;

    current = current_dir;
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

/* Helper function to update an environment variable by key */
void update_env_var(char* key, char* value)
{

    t_envnode *var;
    
    // if (!key || !value)
    //     return (NULL);
    var = NULL;
    var = find_env_var(key, var);
    if (var != NULL)
    {
        free(var->value);
        var->value = strdup(value);
    }
}

int ft_setenv(char *name, char *value, t_envnode **env)
{
    t_envnode *var = find_env_var(name, *env);

    if (var)
    {
        // Variable already exists, update its value
        free(var->value);
        var->value = ft_strdup(value);
    } 
    else 
    {
        // Variable does not exist, add it to the list
        t_envnode *new_var = create_mini_envvar_node(ft_strdup(name), ft_strdup(value));
        ft_add_envlist(new_var, env);
    }
    return 0;  // Success
}

void ft_add_envlist(t_envnode *new_node, t_envnode **env)
{
    t_envnode *curr_node = *env;

    // If the list is empty, set the new node as the head of the list
    if (curr_node == NULL)
    {
        *env = new_node;
        return;
    }

    // Traverse the list until the end is reached
    while (curr_node->next != NULL)
    {
        curr_node = curr_node->next;
    }

    // Add the new node to the end of the list
    curr_node->next = new_node;
}