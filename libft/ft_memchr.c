/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:22:26 by vgejno            #+#    #+#             */
/*   Updated: 2021/12/23 16:10:38 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*ptr_str;
	size_t			i;

	i = 0;
	ptr_str = (unsigned char *)str;
	while (i < n)
	{
		if (ptr_str[i] == ((unsigned char)c))
			return (&ptr_str[i]);
		i++;
	}
	return (NULL);
}
