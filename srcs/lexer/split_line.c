#include "../../headers/minishell.h"

int ft_word_len(char *str)
{
   int len;

   len = 0;
   while (*str != '\0' && *str != ' ' && *str != '\t' && *str != '\n')
   {
       str++;
       len++;
   }
   return (len);
}

char *ft_fill_word(char *str)
{
   int i;
   int word_len;
   char    *word;

   i = 0;
   word_len = ft_word_len(str);
   word = malloc(sizeof(char) * (word_len + 1));
   word[word_len] = '\0';
   while (i < word_len)
   {
       word[i] = str[i];
       i++;
   }
   return (word);
}

void    ft_fill_array(char *str, char **array)
{
   int word_count;

   word_count = 0;
   while (*str == ' ' || *str == '\t' || *str == '\n')
       str++;
   while (*str != '\0')
   {
       array[word_count] = ft_fill_word(str);
       word_count++;
       while (*str != '\0' && *str != ' ' && *str != '\t' && *str != '\n')
           str++;
       while (*str == ' ' || *str == '\t' || *str == '\n')
           str++;
   }
}

int ft_count_words(char *str)
{
   int count;

   count = 0;
   while (*str == ' ' || *str == '\t' || *str == '\n')
       str++;
   while (*str != '\0')
   {
       count++;
       while (*str != '\0' && *str != ' ' && *str != '\t' && *str != '\n')
           str++;
       while (*str == ' ' || *str == '\t' || *str == '\n')
           str++;
   }
   return (count);
}

char    **ft_split(char *str, char *set)
{
   int word_count;
   char **array;

	while (*str != '\'' || *str != '"')
	{
		word_count = ft_count_words(str);
		array = malloc(sizeof(char *) * (word_count + 1));
		array[word_count] = 0;
		ft_fill_array(str, array);
	}
   return (array);
}
