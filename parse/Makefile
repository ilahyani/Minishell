NAME = minishell

CC = cc 

LDFLAGS="-L/Users/mjlem/.brew/opt/readline/lib"

CPPFLAGS="-I/Users/mjlem/.brew/opt/readline/include"

CFLAGS = -Wall -Wextra -Werror 

SRC = minishell.c parser.c lexer.c lists.c grammar.c

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