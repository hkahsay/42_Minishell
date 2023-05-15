#include "../../headers/minishell.h"

int	is_lim_char(char c)
{
	if ((c == '>' || c == '<' || c == '|'))
		return (1);
	return (0);
}

static int	process_lim(char **p, t_token **head, t_lim *lim)
{
	add_token(head, lim->lim_str, lim->lim_type);
	if (ft_strlen(*p) - (size_t)lim->lim_len >= 0)
	{
		*p = *p + (lim->lim_len);
		return (1);
	}
	if (is_q(**p) == 1)
		return (1);
	return (0);
}

char	*check_lim(char **p, t_token **head)
{
	t_lim			*lim;
	unsigned long	i;
	const t_lim		lims[] = {{">>", 2, T_ROA}, {"<<", 2, T_RHD}, {">", 1, \
	T_RO}, {"<", 1, T_RI}, {"|", 1, T_PP}};

	lim = (t_lim *)lims;
	i = 0;
	while (lim->lim_str && (i < sizeof(lims) / sizeof(t_lim)))
	{
		if (**p == *lim->lim_str && (lim->lim_len == 1 || \
		strncmp(*p, lim->lim_str, lim->lim_len) == 0))
		{
			if (process_lim(p, head, lim))
				return (*p);
			else
				break ;
		}
		++lim;
		i++;
		if (lim->lim_str == NULL && i < sizeof(lims) / sizeof(t_lim))
			break ;
	}
	return (*p);
}
