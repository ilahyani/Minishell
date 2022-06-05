all:
	cc -Wall -Wextra -Werror -lreadline *.c -o minishell
clean:
	rm minishell