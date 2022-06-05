LIB = ./libft/libft.a

all: $(LIB)
	@cc -Wall -Wextra -Werror -lreadline $(LIB) *.c -o minishell

clean:
	@rm -rf minishell