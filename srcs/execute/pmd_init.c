#include "../../headers/minishell.h"

t_pmd *init_pmd(void) // t_pline **pline_head
{
	t_pmd *pmd;

	pmd = malloc(sizeof(t_pmd));
	if (pmd != NULL)
		ft_memset(pmd, 0, sizeof(t_pmd));
	return (pmd);
}
