#include"../minishell.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_strlen(const char *str)
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

static char	*ft_str_size(const char *str, int start, int end)
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

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	int		temp;
	char	**split;

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dst;

	if (!s)
		return (0);
	if (start > ((unsigned int)ft_strlen(s)))
		return (strdup(""));
	i = ft_strlen(s) - start;
	if (len > i)
		len = i;
	else if (len < i)
		i = len;
	else if (i < 0)
		i = 0;
	dst = (char *)malloc(sizeof(*s) * (len + 1));
	if (!dst)
		return (0);
	strlcpy(dst, s + start, i + 1);
	return (dst);
}
