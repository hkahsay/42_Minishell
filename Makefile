
NAME = minishell

CC = gcc


FLAG = -Wall -Werror -Wextra -g #-fsanitize=address

RLIB = /Users/$(USER)/.brew/Cellar/readline/8.2.1/lib -lreadline

RINC = .brew/Cellar/readline/8.2.1/include/readline

RM = rm -f


SRCS = src/main.c \
	src/token.c \
	src/utils.c \
	src/init.c \
	src/check.c \



OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: 	${OBJS}
			${CC} ${FLAG} -L ${RLIB} ${OBJS} -o ${NAME}

%.o : %.c
	${CC} ${FLAG} -I ${RINC} -c $^ -o $@

clean:
	${RM} ${OBJS}
	
fclean: clean
	${RM} ${NAME}

	
re: fclean all

.PHONY: all re clean fclean		 