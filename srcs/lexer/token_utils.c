#include "../../headers/minishell.h"

size_t	ft_strcspn(const char *str, const char *charset)
{
	const char *p;
	const char *q;
	size_t count;

	p = str;
	count = 0;
	while (*p != '\0')
	{
		q = charset;
		while (*q != '\0')
		{
			if (*p == *q)
				return (count);
			q++;
		}
		p++;
		count++;
	}
	return (count);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char *ret = dest;

	while (n > 0 && *src != '\0')
	{
		*dest++ = *src++;
		n--;
	}
	while (n > 0)
	{
		*dest++ = '\0';
		n--;
	}
	return ret;
}

//fnct from example
int	ft_strchars_i(const char *s, char *set)
{
	int				i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (ft_strchr(set, s[i]))
			return (i);
		i++;
	}
	return (-1);
}	
