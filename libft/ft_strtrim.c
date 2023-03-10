/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:59:50 by vgejno            #+#    #+#             */
/*   Updated: 2021/12/21 17:21:59 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s, const char *set)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	n;

	if (!s || !set)
		return (0);
	i = 0;
	while (s[i] && ft_strchr(set, s[i]))
		i++;
	j = ft_strlen(s);
	while (j > i && ft_strchr(set, s[j - 1]))
		j--;
	ptr = (char *)malloc(j - i + 1);
	if (!ptr)
		return (0);
	n = 0;
	while (i < j)
		ptr[n++] = s[i++];
	ptr[n] = 0;
	return (ptr);
}
