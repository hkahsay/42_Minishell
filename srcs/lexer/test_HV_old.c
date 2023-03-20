
#include "../../headers/minishell.h"

# define OPEN 1
# define CLOSED 0

// static int	ft_strchr(const char	*s, int c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == (char)c)
// 		{
// 			return (1);
// 		}
// 		i++;
// 	}
// 	if (c == 0)
// 		return (0);
// 	return (0);
// }

static int ft_wordlen(char *str)
{
    int i = 0;

    while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        ++i;
    return (i);
}

static char    *word_dupe(char *str)
{
    int i = 0;
    int len = ft_wordlen(str);
    char *word = malloc(sizeof(char) * (len + 1));

    word[len] = '\0';
    while (i < len)
    {
        word[i] = str[i];
        ++i;
    }
    return (word);
}

static void    fill_words(char **array, char *str)
{
    int word_index = 0;

    while (*str == ' ' || *str == '\t' || *str == '\n')
        ++str;
    while (*str != '\0')
    {
        array[word_index] = word_dupe(str);
        ++word_index;
        while (*str != '\0' && *str != ' ' && *str != '\t' && *str != '\n')
            ++str;
        while (*str == ' ' || *str == '\t' || *str == '\n')
            ++str;
    }
}

static int     count_words(char *str, char *q)
{
    int num_words = 0;
	int	pair_quote = 0;
    int flag_quote = 0;
    // char *str = p;
    while (*str == ' ' || *str == '\t' || *str == '\n')
        {
            printf("\nnum_words: %d\n", num_words);
			printf("\n01:flag_quote: %d *str: %c\n", flag_quote, *str);
			while (*str != '\0' && *str != ' ' && *str != '\t' && *str != '\n') // && *str != q
			{

				printf("\n02:flag_quote: %d *str: %c\n", flag_quote, *str);
				//case 1
				if (!(strncmp(str, q, 1) && flag_quote == CLOSED)) //if she found " and flag 0
				{
					flag_quote = OPEN;
					printf("\n03:found open quote: %d *str: %c\n", flag_quote, *str);
					str++;
					while (*str && (strncmp(str, q, 1))) //continue without " found
						str++;		
					if (!(strncmp(str, q, 1)  && flag_quote == OPEN)) //if she found " and flag 1
					{
						flag_quote = CLOSED;
						printf("\n8:found closed quote: %d *str: %c\n", flag_quote, *str);
						pair_quote++;
						str++;
						// break ;
					}
            		}
				//case 2
				if (!(strncmp(str, q, 1) && flag_quote == OPEN))
				{
					flag_quote = CLOSED;
					printf("\n04:found closed quote: %d *str: %c\n", flag_quote, *str);
					pair_quote++;
					str++;
					// break ;
				}
				else
					str++;
			}
			str++;
		}
    while (*str != '\0')
    {
        printf("\nnum_words: %d\n", num_words);
		printf("\n1:flag_quote: %d *str: %c\n", flag_quote, *str);
        while (*str != '\0' && *str != ' ' && *str != '\t' && *str != '\n') // && *str != q
        {

            printf("\n2:flag_quote: %d *str: %c\n", flag_quote, *str);
			//case 1
			if (!(strncmp(str, q, 1) && flag_quote == CLOSED)) //if she found " and flag 0
            {
                flag_quote = OPEN;
				printf("\n3:found open quote: %d *str: %c\n", flag_quote, *str);
				str++;
                while (*str && (strncmp(str, q, 1))) //continue without " found
					str++;
				if (!(strncmp(str, q, 1) && flag_quote == OPEN)) //if she found " and flag 1
				{
					flag_quote = CLOSED;
					printf("\n3:found closed quote: %d *str: %c\n", flag_quote, *str);
					pair_quote++;
					str++;
					// break ;
				}
            }
			//case 2
            if (!(strncmp(str, q, 1) && flag_quote == OPEN))
            {
                flag_quote = CLOSED;
                printf("\n4:found closed quote: %d *str: %c\n", flag_quote, *str);
                pair_quote++;
				str++;
				// break ;
            }
			else
				str++;
		}
        while (*str == ' ' || *str == '\t' || *str == '\n')
        {
            printf("\nnum_words: %d\n", num_words);
			printf("\n5:flag_quote: %d *str: %c\n", flag_quote, *str);
			while (*str != '\0' && *str != ' ' && *str != '\t' && *str != '\n') // && *str != q
			{

				printf("\n6:flag_quote: %d *str: %c\n", flag_quote, *str);
				//case 1
				if (!(strncmp(str, q, 1) && flag_quote == CLOSED)) //if she found " and flag 0
				{
					flag_quote = OPEN;
					printf("\n7:found open quote: %d *str: %c\n", flag_quote, *str);
					str++;
					while (*str && (strncmp(str, q, 1))) //continue without " found
						str++;		
					if (!(strncmp(str, q, 1)  && flag_quote == OPEN)) //if she found " and flag 1
					{
						flag_quote = CLOSED;
						printf("\n8:found closed quote: %d *str: %c\n", flag_quote, *str);
						pair_quote++;
						str++;
						// break ;
					}
            		}
				//case 2
				if (!(strncmp(str, q, 1) && flag_quote == OPEN))
				{
					flag_quote = CLOSED;
					printf("\n3:found closed quote: %d *str: %c\n", flag_quote, *str);
					pair_quote++;
					str++;
					// break ;
				}
				else
					str++;
			}
			str++;
		}
		++num_words;
	}

    printf("final num_words: %d\n", num_words);
	printf("\npair_quote: %d\n", pair_quote);
	printf("flag_quote: %d\n", flag_quote);
	if (flag_quote == OPEN)
		printf("error");
    return (num_words);
}

char    **split_line(char *str)
{
    int     num_words;
    char    **array;
	char *quote = "\"";

    num_words = count_words(str, quote);
    array = malloc(sizeof(char *) * (num_words + 1));

    array[num_words] = 0;
    fill_words(array, str);
    return (array);
}

// int  main(int ac, char **av)
// {
// 	int i = 0;
// 	int	j = 0;
// 	char **array;

// 	if(ac < 2)
// 	{
// 		return(1);
// 	}

// 	while (i < ac)
// 	{
// 		array = ft_split(av[i]);
// 		while (array[j])
// 		{
// 			printf("%s\n", array[j]);
// 			j++;
// 		}
// 		i++;
// 	}
	
// 	return (0);
	
// }
