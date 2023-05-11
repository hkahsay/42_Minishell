#include "libft.h"

// void* my_my_malloc( size_t size)
// {
// 	void*		addr;
// 	t_list*	node;

// 	addr = my_malloc(size);
// 	if (addr == NULL)
// 	{
// 		printf("Memory allocation failed!\n");
// 		exit(1);
// 	}
// 	node = my_malloc(sizeof(t_list));
// 	node->addr = addr;
// 	node->next = ppline->my_malloc_head;
// 	ppline->my_malloc_head = node;
// 	return (addr);
// }

// void my_free_all(t_list **head)
// {
// 	t_list	*node;

// 	node = *head;
// 	while (*head != NULL)
// 	{
// 		node = *head;
// 		*head = (*head)->next;
// 		free(node->addr);
// 		free(node);
// 	}
// }

static t_list	**finder(void)
{
	static t_list	*wrm;

	return (&wrm);
}

void	*my_malloc(unsigned long size)
{
	char	*buffer;
	t_list	*new_elem;

	buffer = malloc(size);
	if (!buffer)
	{
		destroy_all();
		ft_putstr("ERROR my_malloc\n");
		exit (1);
	}
	new_elem = malloc(sizeof(t_list));
	if (!new_elem)
	{
		free(buffer);
		destroy_all();
		ft_putstr("ERROR my_malloc\n");
		exit (1);
	}
	new_elem->content = buffer;
	// printf("new_elem->content %p\n", new_elem->content);
	new_elem->next = 0;
	ft_lstadd_back(finder(), new_elem);
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
		// printf("current->content%s\n", current->content);
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
		// printf("current->content22%s\n", current->content);
		free(current->content);
		free(current);
		current = next;
	}
	*wrstart = 0;
}


void ft_putchar(char c)
	{
	write(1, &c, 1);
	}

int    ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return(i);
}
