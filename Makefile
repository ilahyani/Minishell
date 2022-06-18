LIB = ./libft/libft.a

LIBFT = ./libft

NAME = minishell

all: $(LIB)
	cc -Wall -Wextra -Werror -lreadline $(LIB) *.c -o $(NAME)

$(LIB):
	Make -C $(LIBFT)

clean:
	rm -rf $(LIB) libft/*.o

fclean:	clean
		rm $(NAME)