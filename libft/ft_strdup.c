/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkahsay <hkahsay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:53:35 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/15 18:05:35 by hkahsay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dst;
	size_t	len;

	// printf("Str 1\n");
	len = 0;
	// printf("Str 2\n");
	// if (!str)
	// 	return (NULL);
	// printf("Str 2.5\n");
	dst = my_malloc(sizeof(char) * ((ft_strlen(str) + 1)));
	// printf("Str 3\n");
	if (!dst || !str)
		return (NULL);
		// printf("Str 4\n");
	while (str[len])
	{
		// printf("Str 5\n");
		dst[len] = str[len];
		// printf("Str 6\n");
		len++;
		// printf("Str 7\n");
	}
	// printf("Str 8\n");
	dst[len] = '\0';
	// printf("Str 9\n");
	return (dst);
}
