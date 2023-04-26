/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:10:31 by vgejno            #+#    #+#             */
/*   Updated: 2021/12/23 17:24:38 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (haystack == NULL && needle == NULL)
		return (NULL);
	if (*needle == 0 || needle == NULL)
		return ((char *)haystack);
	while (haystack[i] && i < n)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && ((i + j) < n))
		{
			if (needle [j + 1] == 0)
				return (&((char *)haystack)[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
