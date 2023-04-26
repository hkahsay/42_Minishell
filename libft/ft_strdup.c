/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:53:35 by vgejno            #+#    #+#             */
/*   Updated: 2023/04/21 17:13:27 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dst;
	size_t	len;

	len = 0;
	dst = my_malloc(sizeof(char) * ((ft_strlen(str) + 1)));
	if (!dst || !str)
		return (NULL);
	while (str[len])
	{
		dst[len] = str[len];
		len++;
	}
	dst[len] = '\0';
	return (dst);
}
