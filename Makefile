CC = gcc

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

SRC	=	minishell.c dynarray2.c dynarray.c ft_str.c ft_mems.c ft_env.c \
		ft_print.c ft_builtins.c ft_sig.c check_token.c ft_is.c ft_quote.c \
		indexer.c parser.c string_utils.c convert_env_var.c ft_token.c main.c \
		redo_split.c unload.c

SRC_D = srcs
SRC_C = $(addprefix ${SRC_D}/, ${SRC})

INC = dynarray.h minishell.h
INC_D = includes
INC_H = $(addprefix ${INC_D}/, ${INC})

all: $(NAME)

$(NAME): ${INC_H} ${SRC_C}
	${CC} ${CFLAGS} ${SRC_C} -I${INC_D} -o ${NAME} -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
