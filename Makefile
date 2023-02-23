# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 11:19:05 by vgejno            #+#    #+#              #
#    Updated: 2023/02/23 12:07:14 by vgejno           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
FLAG = -Wall -Werror -Wextra
RLIB = /Users/$(USER)/.brew/Cellar/readline/8.2.1/lib -lreadline
RINC = .brew/Cellar/readline/8.2.1/include/readline
RM = rm -f

SRCS = main.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAG} -L ${RLIB} ${OBJS} -o ${NAME}

%.o : %.c
	${CC} ${FLAG} -I ${RINC} -c $^ -o $@

clean:
	${RM} ${OBJS}
	
fclean: clean
	${RM} ${NAME}
	
re: fclean all

.PHONY: all re clean fclean		 