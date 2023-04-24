/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:40:41 by vgejno            #+#    #+#             */
/*   Updated: 2021/12/22 13:15:03 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dst, const char	*src, size_t	dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	n;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	n = 0;
	if (dstsize == 0)
		return (dstsize + srclen);
	if (dstsize > dstlen)
	{
		while (*dst)
			dst = dst + dstlen;
		while (*src && n < (dstsize - dstlen - 1))
		{
			*dst++ = *src++;
			n++;
		}
		*dst = '\0';
	}
	if (dstsize <= dstlen)
		return (dstsize + srclen);
	return (dstlen + srclen);
}
