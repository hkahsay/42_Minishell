# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct s_my_malloc_node
{
	void	*addr;
	struct	s_my_malloc_node	*next;
} t_my_malloc_node;

typedef struct s_my_malloc
{
	t_my_malloc_node *head;
} t_my_malloc;

void* my_my_malloc(size_t size)
{
	void*		addr;
	t_my_malloc_node	*node;
	t_my_malloc	my_head;
	// t_ppline *ppline;

	// ppline = get_ppline(NULL);
	addr = my_malloc(size);
	if (addr == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(1);
	}
	node = my_malloc(sizeof(t_my_malloc_node));
	node->addr = addr;
	// printf("PPLINE: %p\n", ppline);
	node->next = my_head.head;
	my_head.head = node;
	// get_ppline(ppline);
	// my_free(ptr, my_head);
	return (addr);
}

void my_free() //void* ptr, t_my_malloc my_head
{
	void* ptr = NULL;
	t_my_malloc my_head;

	if (ptr == NULL)
		return;

	t_my_malloc_node *curr = my_head.head; // Accessing the head from the passed t_my_malloc pointer

	if (curr != NULL && curr->addr == ptr)
	{
		my_head.head = curr->next;
		free(curr);
		free(ptr);
		return;
	}

	while (curr != NULL && curr->addr != ptr)
	{
		curr = curr->next;
	}

	if (curr == NULL)
	{
		printf("Error: Invalid pointer passed to my_free()\n");
		exit(1);
	}

	my_head.head = curr->next;
	free(curr);
	free(ptr);
}


char	*ft_strdup2(const char *str, t_my_malloc *head)
{
	char	*dst;
	size_t	len;

	len = 0;
	dst = my_my_malloc(sizeof(char) * ((strlen(str) + 1)));
	printf("my_my_malloc address: %p\n", dst);
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

char	*ft_strdup1(const char *str)
{
	char	*dst;
	size_t	len;

	len = 0;
	dst = my_malloc(sizeof(char) * ((strlen(str) + 1)));
	printf("my_malloc address: %p\n", dst);
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

int main()
{

	char *str = "hello";
	char *dst;
	printf("ft_strdup1: %s\n", ft_strdup1(str));
	printf("ft_strdup2: %s\n", ft_strdup2(str));
	my_free();
	return(0);
}
