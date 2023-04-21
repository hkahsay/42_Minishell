/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkahsay <hkahsay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:53:35 by vgejno            #+#    #+#             */
/*   Updated: 2023/04/21 18:07:29 by hkahsay          ###   ########.fr       */
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
