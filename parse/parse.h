/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:05:11 by mjlem             #+#    #+#             */
/*   Updated: 2022/07/25 16:42:53 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

# define PIPE '|'
# define OUT_REDIR '>'
# define IN_REDIR '<'
# define EXPAND '$'
# define SQ_STR '\''
// # define DQ_STR '\"'
# define WORD 'W'
# define W_SPACE 'S'
# define RE_ADD 'A'
# define HERE_DOC 'H'
# define ERR -1
# define RE 2

typedef struct s_token{
	int				type;
	char			*arg;
	struct s_token	*next;
}	t_token;

typedef struct s_node
{
	int				type;
	char			**cmd;
	struct s_node	*next;
}	t_node;

typedef struct s_env
{
	char			*var;
    char            *value;
	struct s_env     *next;
}	t_env;

t_node	*parser(char *line, t_env *lst_env);
void	add_lst(t_token **head, t_token *node);
t_token	*lst_new(char	*arg, int type);
t_token	*lexer(char *line);
int		pipeline(t_token **tokens);
void	add_node(t_node **head, t_node *node);
t_node	*new_node(int type, char **arg);
void	free_tab(char **tab);

#endif