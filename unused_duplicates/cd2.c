int ft_cd(t_ppline **ppline) {
    t_env *home = NULL;
    t_env *pwd = NULL;

    if (find_env_vars(*ppline, &home, &pwd) == -1) {
        return -1;
    }

    char *dir = (*ppline)->ppline_cmd[1];
    if (dir == NULL || strcmp(dir, "~") == 0) {
        if (change_dir(home->value) == -1) {
            return -1;
        }
    } else if (strcmp(dir, "-") == 0) {
        if (change_dir_to_oldpwd(pwd, ppline) == -1) {
            return -1;
        }
    } else {
        if (change_dir(dir) == -1) {
            return -1;
        }
    }

    if (update_env_vars(pwd, *ppline) == -1) {
        return -1;
    }

    return 0;
}

int find_env_vars(t_ppline *ppline, t_env **home, t_env **pwd) {
    t_env *env = ppline->pp_list_env;

    while (env != NULL) {
        if (strcmp(env->name, "HOME") == 0) {
            *home = env;
        } else if (strcmp(env->name, "PWD") == 0) {
            *pwd = env;
        }
        env = env->next;
    }

    if (*home == NULL) {
        fprintf(stderr, "cd: HOME environment variable not set\n");
        return -1;
    }

    return 0;
}

int change_dir(const char *dir) {
    if (chdir(dir) == -1) {
        perror("cd");
        return -1;
    }

    return 0;
}

int change_dir_to_oldpwd(t_env *pwd, t_ppline **ppline) {
    t_env *oldpwd = find_env_var("OLDPWD", &(*ppline)->pp_list_env);

    if (oldpwd == NULL) {
        fprintf(stderr, "cd: OLDPWD not set\n");
        return -1;
    }

    if (change_dir(oldpwd->value) == -1) {
        return -1;
    }

    printf("%s\n", oldpwd->value);
    ft_setenv("OLDPWD", pwd->value, &(*ppline)->pp_list_env);
    ft_setenv("PWD", oldpwd->value, &(*ppline)->pp_list_env);

    return 0;
}

int update_env_vars(t_env *pwd, t_ppline *ppline) {
    ft_setenv("OLDPWD", pwd->value, &ppline->pp_list_env);
    ft_setenv("PWD", getcwd(NULL, 0), &ppline->pp_list_env);

    return 0;
}
