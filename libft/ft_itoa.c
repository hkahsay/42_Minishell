/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:56:02 by vgejno            #+#    #+#             */
/*   Updated: 2023/04/21 17:13:11 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	nbr_len(int *nbr, int *neg)
{
	if (*nbr < 0)
	{
		(*neg)++;
		if (*nbr == -2147483648)
		{
			(*neg)++;
			(*nbr)++;
		}
		*nbr = *nbr * -1;
	}
}

static char	*ft_malloc(char *s, int n)
{
	char	*ret;
	int		i;

	i = -1;
	ret = (char *)my_malloc(n + 1);
	if (!ret)
		return (0);
	while (s[++i])
		ret[i] = s[i];
	ret[i] = '\0';
	return (ret);
}

static char	*ft_switch(char *res)
{
	char	ret[12];
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (res[i])
		i++;
	i--;
	while (i >= 0)
	{
		ret[k++] = res[i--];
	}
	ret[k] = '\0';
	return (ft_malloc(ret, k));
}

char	*ft_itoa(int nbr)
{
	char	res[12];
	int		neg;
	int		i;

	i = 0;
	neg = 0;
	nbr_len(&nbr, &neg);
	while (nbr > 9)
	{
		res[i++] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	res[i++] = (nbr % 10) + '0';
	if (neg == 2)
		res[0] = '8';
	if (neg > 0)
		res [i++] = '-';
	res[i] = '\0';
	return (ft_switch(res));
}
