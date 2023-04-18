# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 11:19:05 by vgejno            #+#    #+#              #
#    Updated: 2023/04/18 13:42:04 by vgejno           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SANITIZE = -fsanitize=address
CC = gcc
FLAGS = -Wall -Werror -Wextra
FLAGS += -g
FLAGS += ${SANITIZE}

RLIB = -L/Users/$(USER)/.brew/Cellar/readline/8.2.1/lib -lreadline
RINC = -I.brew/Cellar/readline/8.2.1/include/readline
LIBFT = libft/libft.a
#RLIB = -L/opt/homebrew/Cellar/readline/8.2.1/lib -lreadline

# << HEADERS >> #
#DIR_SRCS = ./srsc
#DIR_OBJS = ./objs
DIR_INCS = ./headers/
INCS = ${DIR_INCS}/minishell.h
INCS += ${DIR_INCS}/structure.h

MAKE = make -s
RM = rm -rf

# << SOURCES >> #
DIR_SRCS = ./srcs
DIR_SRCS += ./srcs/sig_handler
DIR_SRCS += ./srcs/init
DIR_SRCS += ./srcs/mini_env
DIR_SRCS += ./srcs/lexer
DIR_SRCS += ./srcs/token
DIR_SRCS += ./srcs/parser
DIR_SRCS += ./srcs/built_in
DIR_SRCS += ./srcs/execute
DIR_SRCS += ./srcs/print
DIR_SRCS += ./srcs/error
DIR_SRCS += ./srcs/free
#DIR_SRCS += ./srcs/parser
SRCS = ${DIR_SRCS}/main.c
#SRCS += ${DIR_SRCS}/..

# << OBJECTS >> #
DIR_OBJS = ./objs
OBJS = ${addprefix ${DIR_OBJS}/, ${notdir ${SRCS:.c=.o}}}

SRCS =	srcs/main.c \
		srcs/sig_handler/signal_handler.c \
		srcs/init/envnode_init.c \
		srcs/init/token_init.c \
		srcs/init/parse_init.c \
		srcs/init/pmd_init.c \
		srcs/mini_env/free_mini_env.c \
		srcs/mini_env/env_util.c \
		srcs/mini_env/create_envnode.c \
		srcs/mini_env/setenv.c \
		srcs/lexer/interpret.c \
		srsc/lexer/interp_delim.c \
		srcs/lexer/interp_quotes.c \
		srcs/lexer/interp_word.c \
		srcs/lexer/interp_space.c \
		srcs/token/token_list.c \
		srcs/token/token_expand.c \
		srcs/token/token_space.c \
		srcs/token/token_merge.c \
		srcs/token/token_new.c \
		srcs/token/token_utils.c \
		srcs/parser/parse.c \
		srcs/parser/parse_cmd.c \
		srcs/parser/parse_utils.c \
		srcs/execute/execute.c \
		srcs/execute/execute_utils.c \
		srcs/execute/create_ppline.c \
		srcs/built_in/builtin.c \
		srcs/built_in/builtin_utils.c \
		srcs/built_in/cd.c \
		srcs/built_in/echo.c \
		srcs/built_in/env.c \
		srcs/built_in/exit.c \
		srcs/built_in/export.c \
		srcs/built_in/pwd.c \
		srcs/built_in/unset.c \
		srcs/print/print_token.c \
		srcs/print/print_cmd.c \
		srcs/print/print_env.c \
		srcs/print/print_ppline.c \
		srcs/error/error_exit.c \
		srcs/error/error_input.c \
		srcs/free/free_token.c \
		srcs/free/my_malloc.c \

DFILES = srcs/${addprefix ${DIR_OBJS}/, ${notdir ${SRCS:.c=.d}}}

vpath %.c ${DIR_SRCS}

all: ${NAME}

${NAME}: 	${OBJS}
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
