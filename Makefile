# << COMPILATION SETTINGS >> #
NAME = minishell

SANITIZE = -fsanitize=address 
CC = gcc
FLAGS = -Wall -Werror -Wextra
FLAGS += -g
FLAGS += ${SANITIZE}

RLIB = -L/Users/$(USER)/.brew/Cellar/readline/8.2.1/lib -lreadline
RINC = -I.brew/Cellar/readline/8.2.1/include/readline
LIBFT = libft/libft.a

# << HEADERS >> #
#DIR_SRCS = ./srsc
#DIR_OBJS = ./objs
DIR_INCS = ./headers/
INCS = ${DIR_INCS}/minishell.h

MAKE = make -s
RM = rm -rf

# << SOURCES >> #
DIR_SRCS = ./srcs
SRCS = ${DIR_SRCS}/main.c
#SRCS += ${DIR_SRCS}/..

# << OBJECTS >> #
DIR_OBJS = ./objs
OBJS = ${addprefix ${DIR_OBJS}/, ${notdir ${SRCS:.c=.o}}}

DFILES = ${addprefix ${DIR_OBJS}/, ${notdir ${SRCS:.c=.d}}}

vpath %.c ${DIR_SRCS}

all: ${NAME}

${NAME}: ${OBJS}
	${MAKE} -C libft
	${CC} ${FLAGS} ${OBJS} ${RLIB} ${LIBFT} -o ${NAME}

${DIR_OBJS}/%.o : %.c | ${DIR_OBJS}
	${CC} ${FLAGS} -I ${RINC} -I ${DIR_INCS} -o $@ -c $^ -MD
include ${wildcard *.d}	

${DIR_OBJS}:
	mkdir -p ${DIR_OBJS}

clean:
	${MAKE} clean -C libft
	${RM} ${DIR_OBJS} ${DFILES}
	
fclean: clean
	${MAKE} fclean -C libft
	${RM} ${NAME}
	
re: fclean all

.PHONY: all re clean fclean 