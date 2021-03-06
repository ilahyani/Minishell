NAME = minishell

CC = cc 

LDFLAGS="-L/Users/$(USER)/.brew/opt/readline/lib"

CPPFLAGS="-I/Users/$(USER)/.brew/opt/readline/include"

CFLAGS = -Wall -Wextra -Werror 

SRC = ./parse/minishell.c ./parse/parser.c ./parse/lexer.c ./parse/lists.c ./parse/grammar.c \
		./exec/env_init.c ./exec/execve.c ./exec/expantion.c ./exec/io_redir.c ./exec/main.c ./exec/my_cd.c ./exec/my_echo.c ./exec/my_env.c ./exec/my_exit.c ./exec/my_export.c ./exec/my_pwd.c ./exec/my_unset.c ./exec/pipe.c ./exec/sig_handle.c ./exec/utils.c

OBJ = $(SRC:%.c=%.o)

LIB = ./libft/libft.a

all: $(NAME)

$(LIB):
	@make -C libft

$(NAME): $(OBJ) $(LIB)
	@cc $(CFLAGS) $(LDFLAGS) $(LIB) -lreadline $(OBJ) -o $(NAME) && clear

clean_lib:
	@make clean -C libft

fclean_lib:
	@make fclean -C libft

clean: clean_lib
	@-rm *.o 

fclean: clean fclean_lib
	@-rm $(NAME)

re: fclean all