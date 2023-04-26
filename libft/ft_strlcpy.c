/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:36:09 by vgejno            #+#    #+#             */
/*   Updated: 2021/12/22 13:47:29 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char	*dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_strlen(src);
	if (!src || !dst)
		return (0);
	if (dstsize)
	{
		while (*src && i < dstsize - 1)
		{
			*dst++ = *src++;
			i++;
		}
		*dst = '\0';
	}
	return (n);
}
