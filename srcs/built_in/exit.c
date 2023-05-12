#include"../../headers/minishell.h"

int	ft_exit(t_ppl **ppl)
{
	int	i;

	i = 0;
	if ((*ppl)->ppl_cmd != NULL)
	{
		i = ft_atoi(*(*ppl)->ppl_cmd);
		printf("exit\n");
		destroy_all();
		exit (i);
	}
	else
	{
		printf("exit\n");
		destroy_all();
		exit (g_exit_status);
	}
	return (0);
}
