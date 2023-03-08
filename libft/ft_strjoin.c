/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:15:48 by vgejno            #+#    #+#             */
/*   Updated: 2021/12/23 15:35:43 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr1;
	char	*ptr2;

	if (!s1 || !s2)
		return (NULL);
	ptr1 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr1)
		return (NULL);
	ptr2 = ptr1;
	while (*s1)
		*(ptr1++) = *(s1++);
	while (*s2)
		*(ptr1++) = *(s2++);
	*ptr1 = '\0';
	return (ptr2);
}
