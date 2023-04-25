#include"../../headers/minishell.h"

// Check if HOME environment variable is set
static int is_home_set(t_ppline *ppline)
{
    t_envnode *home;
    
    home = ppline->pp_list_env;
    while (home != NULL)
    {
        if (strcmp(home->key, "HOME") == 0 && home->value != NULL)
            return (1);
        home = home->next;
    }
    fprintf(stderr, "cd: HOME environment variable not set\n");
    return (0);
}

// Get the directory to change to
static char *get_directory(t_ppline *ppline)
{
    t_envnode *home;
    char *dir;

    home = NULL;
    dir = ppline->ppline_cmd[1];
    if (dir == NULL || strcmp(dir, "~") == 0)
    {
        home = ppline->pp_list_env;
        while (home != NULL)
        {
            if (strcmp(home->key, "HOME") == 0 && home->value != NULL)
                return home->value;
            home = home->next;
        }
        return (NULL);
    }
    return (dir);
}

// Change directory to the specified directory
static int change_directory(char *dir, t_ppline *ppline)
{
    t_envnode *pwd;

    pwd = NULL;
    if (chdir(dir) == -1)
    {
        fprintf(stderr, "cd: %s: %s\n", dir, strerror(errno));
        return (-1);
    }
    pwd = ppline->pp_list_env;
    while (pwd != NULL)
    {
        if (strcmp(pwd->key, "PWD") == 0)
        {
            ft_setenv("OLDPWD", pwd->value, pwd->content, &ppline->pp_list_env);
            break;
        }
        pwd = pwd->next;
    }
    ft_setenv("PWD", dir, pwd->content, &ppline->pp_list_env);
    return (0);
}

// Change directory to the previous directory
static int change_to_previous_directory(t_ppline *ppline)
{
    t_envnode *oldpwd;

    oldpwd = ppline->pp_list_env;
    while (oldpwd != NULL)
    {
        if (strcmp(oldpwd->key, "OLDPWD") == 0 && oldpwd->value != NULL)
            break;
        oldpwd = oldpwd->next;
    }
    if (oldpwd == NULL) 
    {
        fprintf(stderr, "cd: OLDPWD not set\n");
        return (-1);
    }
    if (change_directory(oldpwd->value, ppline) == -1)
        return (-1);
    printf("%s\n", oldpwd->value);
    return 0;
}

// Change the current working directory
int ft_cd(t_ppline **ppline)
{
    char *dir;

    dir = NULL;
    if (!is_home_set(*ppline))
        return -1;
    dir = get_directory(*ppline);
    if (dir == NULL)
    {
        msg_error(dir, 0);
        // fprintf(stderr, "cd: directory not found\n");
        return -1;
    }
    if (strcmp(dir, "-") == 0)
        return (change_to_previous_directory(*ppline));
    return (change_directory(dir, *ppline));
}

// t_envnode *find_env_var(char *var_name, t_envnode **env_list)
// {
//     t_envnode *env = *env_list;
//     while (env != NULL)
//     {
//         if (strcmp(env->key, var_name) == 0)
//         {
//             return env;
//         }
//         env = env->next;
//     }
//     return NULL;
// }
// static t_envnode	*find_home_pwd(char *var_name, t_envnode **home, t_envnode **pwd, t_ppline *ppline)
// {
// 	// t_envnode *home = NULL;
//    	// t_envnode *pwd = NULL;
//     t_envnode   *env;

//     env = ppline->pp_list_env;
// 	 // Find HOME and PWD environment variables
//     while (env != NULL)
// 	{
//         if (strcmp(env->key, "HOME") == 0)
//             *home = env;
//         else if (strcmp(env->key, "PWD") == 0)
//             *pwd = env;
//         env = env->next;
//     }
//     if (*home == NULL)
//     {
//         fprintf(stderr, "cd: HOME environment variable not set\n");
//         return (-1);
//     }
// 	return (env);
// }


// static int change_dir(const char *dir)
// {
//     if (chdir(dir) == -1)
//     {
//         perror("cd");
//         return (-1);
//     }
//     return (0);
// }

// static int change_dir_to_oldpwd(t_envnode *pwd, t_ppline **ppline)
// {
//     t_envnode   *oldpwd;

//     oldpwd = find_home_pwd(*ppline, "OLDPWD", &(*ppline)->pp_list_env);
//     if (oldpwd == NULL)
//     {
//         fprintf(stderr, "cd: OLDPWD not set\n");
//         return -1;
//     }
//     if (change_dir(oldpwd->value) == -1)
//         return -1;
//     printf("%s\n", oldpwd->value);
//     ft_setenv("OLDPWD", pwd->value, pwd->content, &(*ppline)->pp_list_env);
//     ft_setenv("PWD", oldpwd->value, pwd->content, &(*ppline)->pp_list_env);
//     return 0;
// }

// int ft_cd(t_ppline **ppline)
// {
//     t_envnode *env = (*ppline)->pp_list_env;
// 	t_envnode *oldpwd;
//    	t_envnode *home = NULL;
//    	t_envnode *pwd = NULL;
// 	char *dir;

//    	if (find_home_pwd(*ppline, &home, &pwd))
//         return (-1);
//     dir = (*ppline)->ppline_cmd[1];
//     if (dir == NULL || strcmp(dir, "~") == 0) 
// 	{
//         if (change_dir(home->value) == -1)
//             return (-1);
//     } 
// 	else if (strcmp(dir, "-") == 0)
// 	{
//         // If argument is '-', change directory to the previous directory
// 		if (change_dir_to_oldpwd(pwd, ppline) == -1)
//             return(-1);
//     } 
// 	else 
// 	{
//         if (change_dir(dir) == -1)
//             return (-1);
//     }
//     return 0;
// }

// int ft_cd(t_ppline **ppline)
// {
//     t_envnode *env = (*ppline)->pp_list_env;
// 	t_envnode *oldpwd;
//    	t_envnode *home = NULL;
//    	t_envnode *pwd = NULL;
// 	char *dir;
//     // Check if HOME environment variable is set
//     if (home == NULL)
// 	{
//         fprintf(stderr, "cd: HOME environment variable not set\n");
//         return -1;
//     }

//     dir = (*ppline)->ppline_cmd[1];
//     if (dir == NULL || strcmp(dir, "~") == 0) 
// 	{
//         // If no argument is given, change directory to home directory
//         if (chdir(home->value) == -1)
// 		{
//             perror("cd");
//             return -1;
//         }
//     } 
// 	else if (strcmp(dir, "-") == 0)
// 	{
//         // If argument is '-', change directory to the previous directory
// 	    oldpwd = NULL;
//         env = (*ppline)->pp_list_env;
//         while (env != NULL)
// 		{
//             if (strcmp(env->key, "OLDPWD") == 0)
// 			{
//                 oldpwd = env;
//                 break;
//             }
//             env = env->next;
//         }
//         if (oldpwd == NULL)
// 		{
//             fprintf(stderr, "cd: OLDPWD not set\n");
//             return -1;
//         }
//         if (chdir(oldpwd->value) == -1)
// 		{
//             perror("cd");
//             return -1;
//         }
//         printf("%s\n", oldpwd->value);
//         // Update PWD and OLDPWD environment variables
//         ft_setenv("OLDPWD", pwd->value, pwd->content, &(*ppline)->pp_list_env);
//         ft_setenv("PWD", oldpwd->value, oldpwd->content, &(*ppline)->pp_list_env);
//     } 
// 	else 
// 	{
//         // Change directory to the specified directory
//         if (chdir(dir) == -1)
// 		{
//             perror("cd");
//             return -1;
//         }
//         // Update PWD and OLDPWD environment variables
//         ft_setenv("OLDPWD", pwd->value, pwd->content, &(*ppline)->pp_list_env);
//         ft_setenv("PWD", dir, pwd->content, &(*ppline)->pp_list_env);
//     }

//     // Free memory and return success
//     return 0;
// }