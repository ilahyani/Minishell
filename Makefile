NAME = minishell

CC = cc 

LDFLAGS="-L/Users/$(USER)/.brew/opt/readline/lib"
# LDFLAGS="-L/opt/homebrew/opt/readline/lib"

CPPFLAGS="-I/Users/$(USER)/.brew/opt/readline/include"
# CPPFLAGS="-I/opt/homebrew/opt/readline/include"

CFLAGS = -Wall -Wextra -Werror 

SRC = ./main.c ./parse/minishell.c ./parse/parser.c ./parse/lexer.c ./parse/lists.c ./parse/grammar.c ./exec/env_init.c ./exec/env_init_utils.c ./exec/execve.c ./exec/io_redir.c ./exec/io_redir_utils.c ./exec/io_redir_pro_max.c ./exec/my_cd.c ./exec/my_echo.c ./exec/my_env.c ./exec/my_exit.c ./exec/my_export.c ./exec/my_export_list_update.c ./exec/my_export_list_utils.c ./exec/my_export_utils.c ./exec/my_pwd.c ./exec/my_unset.c ./exec/pipe.c ./exec/pipe_utils.c ./exec/sig_handle.c ./exec/utils.c

OBJ = $(SRC:%.c=%.o)

LIB = ./libft/libft.a

all: $(NAME)

$(LIB):
	@make -C libft

$(NAME): $(OBJ) $(LIB)
	@cc $(CFLAGS) $(LDFLAGS) $(LIB) -lreadline $(OBJ) -o $(NAME) && clear
	@echo "Done"

%.o: %.c $(HDR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean_lib:
	@make clean -C libft

fclean_lib:
	@make fclean -C libft

clean: clean_lib
	@-rm ./*.o
	@-rm ./parse/*.o
	@-rm ./exec/*.o

fclean: clean fclean_lib
	@-rm $(NAME)

re: fclean all