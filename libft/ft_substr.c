/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 20:51:25 by vgejno            #+#    #+#             */
/*   Updated: 2021/12/23 13:03:03 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ((unsigned int)ft_strlen(s)))
		return (ft_strdup(""));
	i = ft_strlen(s) - start + 1;
	if (len > i)
		len = i;
	if (len < i)
		i = 0;
	if (len < i)
		i = len;
	ptr = ((char *)malloc((len + 1) * sizeof(char)));
	if (ptr == 0)
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}
