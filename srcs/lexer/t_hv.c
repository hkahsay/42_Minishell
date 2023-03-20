#include<unistd.h>
#include<stdio.h>

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char    *skip_spaces(char *str)
{
	while (ft_isspace(*str))
		str++;
    while (*str)
	{
		if(!ft_isspace(*str))
        	str++;
		printf("str1: %s\n", str);
	}
		
	return (str);
}

int main()
{
	char *str = "  hello world ";
	str = skip_spaces(str);
	printf("str2: %s\n", str);
	return (0);
}