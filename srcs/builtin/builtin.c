#include"../../headers/minishell.h"

int is_builtins(t_builtin_cmds commands)
{

    int builtin_size;
	int i;

	builtin_size = 7;
	i = 0;
	t_builtin_cmds builtins_cmds[] = {
		PWD,
		CD,
		ECHO,
		UNSET,
		EXPORT,
		ENV,
		EXIT
	};
	while (i < builtin_size)
	{
		if (commands == builtins_cmds[i])
			return(1);
		i++;
	}
	return(0);
}

//  static int    is_builtin_type(char *content)
//  {
// 	if (ft_strncmp(content, "echo", ft_strlen(content)))
// 		return (1);
// 	if (ft_strncmp(content, "cd", ft_strlen(content)))
// 		return (1);
// 	if (ft_strncmp(content, "pwd", ft_strlen(content)))
// 		return (1);
// 	if (ft_strncmp(content, "env", ft_strlen(content)))
// 		return (1);
// 	if (ft_strncmp(content, "export", ft_strlen(content)))
// 		return (1);
// 	if (ft_strncmp(content, "unset", ft_strlen(content)))
// 		return (1);
// 	if (ft_strncmp(content, "exit", ft_strlen(content)))
// 		return (1);
// 	return (0);
//  }

 