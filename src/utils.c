#include"../minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	if (!(str))
		return ;
	i = ft_strlen(str);
	write(fd, str, i);
}


static int	ft_count(char const *s, char c)
{
	int	word;
	int	flag;

	word = 0;
	flag = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c && flag == 0)
		{
			flag = 1;
			word++;
		}
		else if (*s == c)
			flag = 0;
		s++;
	}		
	return (word);
}

static char	*ft_str_size(char *str, int start, int end)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc((end - start + 1) * sizeof(char));
	while (start < end)
		dst[i++] = str[start++];
	dst[i] = '\0';
	return (dst);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	int			temp;
	char		**split;

	if (!s)
		return (NULL);
	split = malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = -1;
	j = 0;
	temp = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && temp < 0)
			temp = i;
		else if ((s[i] == c || i == (int)ft_strlen(s)) && temp >= 0)
		{
			split[j++] = ft_str_size(s, temp, i);
			temp = -1;
		}
	}
	split[j] = 0;
	return (split);
}
