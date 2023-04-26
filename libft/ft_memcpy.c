/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:15:09 by vgejno            #+#    #+#             */
/*   Updated: 2021/12/23 17:22:42 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ptr_src;
	unsigned char	*ptr_dst;

	ptr_src = (unsigned char *)src;
	ptr_dst = (unsigned char *)dst;
	if (src == NULL && dst == NULL)
		return (NULL);
	while (n > 0)
	{
		*ptr_dst++ = *ptr_src++;
		n--;
	}
	return (dst);
}
