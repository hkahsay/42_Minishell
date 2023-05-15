/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkahsay <hkahsay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:44:35 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/15 18:06:38 by hkahsay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	**finder(void)
{
	static t_list	*wrm;

	return (&wrm);
}

void	*my_malloc(unsigned long size)
{
	char	*buffer;
	t_list	*new_elem;

	printf("My malloc 1\n");
	buffer = malloc(size);
	printf("My malloc 2\n");
	if (!buffer)
	{
		printf("My malloc 3\n");
		destroy_all();
		printf("My malloc 4\n");
		ft_putstr("ERROR my_malloc\n");
		printf("My malloc 5\n");
		exit (1);
	}
	printf("My malloc 6\n");
	new_elem = malloc(sizeof(t_list));
	printf("My malloc 7\n");
	if (!new_elem)
	{
		printf("My malloc 8\n");
		free(buffer);
		printf("My malloc 9\n");
		destroy_all();
		printf("My malloc 10\n");
		ft_putstr("ERROR my_malloc\n");
		printf("My malloc 11\n");
		exit (1);
	}
	printf("My malloc 12\n");
	new_elem->content = buffer;
	printf("My malloc 13\n");
	new_elem->next = 0;
	printf("My malloc 14\n");
	ft_lstadd_back(finder(), new_elem);
	printf("My malloc 15\n");
	return (buffer);
}

int	my_free(void *ptr)
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;
	t_list	**wrstart;

	prev = 0;
	wrstart = finder();
	current = *wrstart;
	while (current)
	{
		next = current->next;
		if (current->content == ptr)
		{
			free(ptr);
			free(current);
			if (prev)
				prev->next = next;
			else
				*wrstart = next;
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

void	destroy_all(void)
{
	t_list	*current;
	t_list	*next;
	t_list	**wrstart;

	wrstart = finder();
	current = *wrstart;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*wrstart = 0;
}
