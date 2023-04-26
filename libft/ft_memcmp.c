/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:03:12 by vgejno            #+#    #+#             */
/*   Updated: 2021/12/22 11:18:02 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*ptr_str1;
	unsigned char	*ptr_str2;
	size_t			i;

	i = 0;
	ptr_str1 = (unsigned char *)str1;
	ptr_str2 = (unsigned char *)str2;
	while (i < n)
	{
		if (ptr_str1[i] != ptr_str2[i])
			return (ptr_str1[i] - ptr_str2[i]);
		i++;
	}
	return (0);
}
