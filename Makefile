LIB = ./libft/libft.a

READLN = /opt/homebrew/opt/readline/include

RLN = /opt/homebrew/opt/readline/lib

LIBFT = ./libft

NAME = minishell

all: $(LIB)
	cc -Wall -Wextra -Werror -lreadline -I$(READLN) -L$(RLN) $(LIB) *.c -o $(NAME)

$(LIB):
	Make -C $(LIBFT)

clean:
	rm -rf $(LIB) libft/*.o

fclean:	clean
		rm $(NAME)

re:	fclean make