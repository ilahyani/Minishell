LIB = ./libft/libft.a

LIBFT = ./libft

all: $(LIB)
	cc -Wall -Wextra -Werror -lreadline $(LIB) *.c -o minishell

$(LIB):
	Make -C $(LIBFT)

clean:
	rm -rf $(LIB) libft/*.o 