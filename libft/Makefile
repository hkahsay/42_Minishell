# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 16:28:58 by vgejno            #+#    #+#              #
#    Updated: 2023/04/21 17:15:41 by vgejno           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_atoi.c \
 		ft_bzero.c \
 		ft_calloc.c \
 		ft_isalnum.c \
 		ft_isalpha.c \
 		ft_isascii.c \
 		ft_isdigit.c \
 		ft_isprint.c \
		ft_isspace.c \
 		ft_itoa.c \
 		ft_memchr.c \
 		ft_memcmp.c \
 		ft_memcpy.c \
 		ft_memmove.c \
 		ft_memset.c \
 		ft_putendl_fd.c \
 		ft_putnbr_fd.c \
 		ft_split.c \
		ft_strdup.c \
 		ft_striteri.c \
 		ft_strjoin.c \
 		ft_strlcat.c \
 		ft_strlcpy.c \
 		ft_strlen.c \
 		ft_strmapi.c \
 		ft_strncmp.c \
 		ft_strnstr.c \
 		ft_strrchr.c \
		ft_substr.c \
 		ft_tolower.c \
 		ft_toupper.c \
 		ft_strchr.c \
 		ft_strtrim.c \
		ft_malloc.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \

# SRCS_BONUS = 																					\
# 						ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c	\
# 				ft_lstlast.c	ft_lstadd_back.c	ft_lstdelone.c		\
# 				ft_lstclear.c	ft_lstiter.c		
OBJS = ${SRCS:.c=.o}
#********bonus paths******
# OBJS_BONUS = ${SRCS_BONUS:.c=.o}




CC = gcc
RM = RM -f

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): ${OBJS}
	ar rcs $@ $^

%.o : %.c
	${CC} ${CFLAGS} -o $@ -c $<

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all
.PHONY: clean fclean re