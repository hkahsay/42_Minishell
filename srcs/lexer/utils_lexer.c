
#include "../../headers/minishell.h"

static t_stringln	*init_stringln(char *str, size_t len)
{
	t_stringln *newstr;

	if (!str)
		return (NULL);
	newstr = malloc(sizeof(t_stringln) * 1);
	printf("newstr: %p\n", newstr);
	if (!newstr)
	{
		free(str);
		return (NULL);
	}	
	newstr->str = str;
	newstr->len = len;
	printf("newstr: %s\n", newstr->str);
	printf("newstr: %zu\n", newstr->len);
	return (newstr);
}

t_stringln	*ft_strdup_stringln(const char *str)
{
	char		*dst;
	size_t		len;
	t_stringln	*dststr;

	len = 0;
	dststr = NULL;
	dst = malloc(sizeof(char) * ((ft_strlen(str) + 1)));
	if (!dst || !str)
		return (NULL);
	while (str[len])
	{
		dst[len] = str[len];
		len++;
	}
	dst[len] = '\0';
	dststr = init_stringln(dst, len);
	if (!dststr)
		return (NULL);
	// free(dst);	
	return (dststr);
}

char *epur_str(char *str)
{
    char *result; // allocate memory for the result string
    char *p;
    int space_flag = 0;

	if (!str)
		return (0); // to check what we have to return here
	result = malloc(ft_strlen(str) + 1); // allocate memory for the result string
	if (!result)
		return (0);
	p = result;
    // skip leading spaces
    while (ft_isspace(*str))
		str++;
    // copy string with exactly one space between words
    while (*str != '\0')
	{
		if (ft_isspace(*str))
		{
			if (!space_flag)
			{
				*p++ = ' ';
				space_flag = 1;
			}
        }
		else
		{
			*p++ = *str;
			space_flag = 0;
		}
		str++;
	}
    // remove trailing space
    if (space_flag && p > result)
		 p--;
    // add null terminator
    *p = '\0';
    return (result);
}
