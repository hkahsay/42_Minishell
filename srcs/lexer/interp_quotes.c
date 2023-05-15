#include "../../headers/minishell.h"

static void	advance(char **p_q, int *q_len, int *q_status)
{
	(*p_q)++;
	(*q_len)++;
	*q_status = OPEN;
}

static void	manage_status(int *q_status, int *q_len)
{
	(*q_status) = CLOSED;
	(*q_len)++;
}

static char	*manage_close(char **p, t_token **head, char **p_q, int *q_len)
{
	add_token(head, ft_substr(*p, 0, (*p - *p_q)), T_ERQ);
	*p += (*q_len);
	return (*p);
}

static void	init_var(char ***p, char **p_q, int *q_status, int *q_len)
{
	*p_q = **p;
	*q_status = 0;
	*q_len = 0;
}

char	*check_quotes(char **p, t_token **head)
{
	char	*p_q;
	int		q_status;
	int		q_len;

	init_var(&p, &p_q, &q_status, &q_len);
	while (p_q && *p_q)
	{
		if (q_status == CLOSED)
		{
			advance(&p_q, &q_len, &q_status);
			while (*p_q && (!(is_q(*p_q)) || ((eqt(*p)) + (eqt(p_q))) % 2))
				advance(&p_q, &q_len, &q_status);
		}
		else if (is_q(*p_q) && q_status == OPEN)
		{
			manage_status(&q_status, &q_len);
			if (((eqt(*p)) + (eqt(p_q))) % 2 == 0)
				add_token(head, ft_substr(*p, 0, q_len), eqt(*p));
			*p += q_len;
			return (*p);
		}
	}
	if (!(is_q(*p_q)) && q_status == OPEN && *p_q == '\0')
		return (manage_close(p, head, &p_q, &q_len));
	return (*p);
}
