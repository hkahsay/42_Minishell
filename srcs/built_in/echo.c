#include"../../headers/minishell.h"

	int ft_echo(char **args, t_envnode **env_var)
	{
	int i;
	(void)env_var;
	i = 1;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
		i++;
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (args[1] && ft_strcmp(args[1], "-n") != 0) {
		ft_putchar('\n');
	}
	printf("ft_echo\n");
	return 0;
	}

	// void ft_putchar(char c)
	// {
	// write(1, &c, 1);
	// }

	// int    ft_putstr(char *str)
	// {
	// int i;

	// i = 0;
	// while (str[i])
	// {
	// 	ft_putchar(str[i]);
	// 	i++;
	// }
	// return(i);
	// }

// int ft_echo(char **args, t_envnode **env_var)
// {
//     (void)args;
//     (void)env_var;
//     printf("ft_echo\n");
//     return 0;
// }

// static void ft_putchar(char c)
// {
//     write(1, &c, 1);
// }

// static int    ft_putstr(char *str)
// {
//     int i;

//     i = 0;
//     while (str[i])
//     {
//         ft_putchar(*str);
//         i++;
//     }
//     return(i);
// }

// int ft_echo(t_cmd *cmds)//, t_envnode *env
// {
//     int i = 1;  // Start with the first argument (skip "echo")
//     char    **arg; //= {" echo", "hello"};

//     arg = create_array(cmds);
//     // init_args
//     // printf("Cmd->cmd_args: %p\n", cmds->cmd_args);
//     // node = (t_redir_args *)cmds->cmd_args;
//     // node = strdup()
//     // if (!node)
//     //     return (0);
//     // arg = &node->args;
//     // while (node)
//     // {
//     //     ft_putstr(node->args);
//     //     if (node->next)
//     //         node = node->next;
//     //     else
//     //         break ;
//     // }
//     // ft_putstr("\n");

//     // argv = node->args;

//     // Check for the "-n" flag
//     if (arg[i] && strcmp(arg[i], "-n") == 0) {
//         i++;  // Skip the flag
//     }

//     // Print each argument followed by a space, except the last one
//     while (arg[i])
//     {
//         ft_putstr(arg[i]);
//         if (arg[i + 1])
//             ft_putchar(' ');
//         i++;
//     }
//     // Print a newline character unless the "-n" flag was used
//     if (arg[1] && ft_strcmp(arg[1], "-n") != 0) {
//         ft_putchar('\n');
//     }
//     return 0;  // Return success
// }

//   flag_n = 1; option -n is exists
//     counter[0] = 0;  loop counter
//     counter[1] = 0; keep track whether the current is arg 1st or not
//     node = cmds->cmd_args;  structure ponited to cmd_args use to store info current args
//     argv = node->all_cmds; enters loop that iterats throurgh argv starts from 2nd args
//     argv[0] is the name of cmd itself so skipps

// int builtin_echo(t_cmd   *cmds)
// {
//     int flag_n;
//     int counter[2];
//     char    **argv;
//     t_pipeline  *node;

//     flag_n = 1; //option -n is exists
//     counter[0] = 0;
//     counter[1] = 0;
//     node = cmds->cmd_args;
//     argv = node->all_cmds;
//     while (argv && argv[counter[0]])
//     {
//         if ((!counter[1] && ft_strncmp(argv[counter[0]], "-n", 2)== 0) &&
//             (count_char(argv[counter[0]], 'n') == (int)ft_strlen(argv[counter[0]] - 1)))
//             flag_n = 0;
//         else
//         {
//             counter[1] = 1;
//             ft_putstr_fd(argv[counter[0]], 1);
//             if (argv[counter[0] + 1])
//                 ft_putchar_fd(' ', 1);
//         }
//         ++counter[0];
//     }
//     return (write(1, "\n", flag_n) == 2);
// }
