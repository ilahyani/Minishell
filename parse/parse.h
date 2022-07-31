/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:05:11 by mjlem             #+#    #+#             */
/*   Updated: 2022/08/01 00:15:34 by mjlem            ###   ########.fr       */
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
# include "../minishell.h"

# define PIPE '|'
# define OUT_REDIR '>'
# define IN_REDIR '<'
# define EXPAND '$'
# define SQ_STR '\''
# define WORD 'W'
# define W_SPACE 'S'
# define RE_ADD 'A'
# define HERE_DOC 'H'

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

int		redirction(t_token **tokens);
int		simple_cmd_elm(t_token **tokens);
int		check_pipe(t_token **tokens);
int		simple_cmd(t_token **tokens);
int		command(t_token **tokens);
int		my_pipe(t_token **tokens, int i);
int		pipeline(t_token **tokens);
int		my_redirection(t_token **tokens, char *line, int i);
int		var_delimiter(char c);
int		special_char(char c);
int		reserved_char(char c);
int		single_quote(t_token **tokens, char *line, int i);
int		dollar_sign(t_token **tokens, char *line, int i);
int		double_quote(t_token **tokens, char *line, int i);
int		get_word(t_token **tokens, char *line, int i);
int		space(t_token **tokens, char *line, int i);
int		heredoc_here(int type);
char	*expand_exit_code(char *arg);

void	word(t_token **tokens, t_node **line);
void	parse_pipe(t_token **tokens, t_node **line);
void	parse_re(t_node **line, t_token **tokens);
void	parse_heredoc(t_node **line, t_token **tokens);
t_node	*parse(t_token **tokens);
t_token	*lexer(char *line);
char	**add_to_table(char **tmp2, char *tmp1);
char	**join_2d(char **arg1, char **arg2);
void	add_lst(t_token **head, t_token *node);
t_node	*move_node(t_node *node, t_node *head, t_node **origin);
t_node	*join_words(t_node *list);
t_node	*adjuste_list(t_node *list);
t_token	*lst_new(char	*arg, int type);
t_token	*lexer(char *line);
int		pipeline(t_token **tokens);
void	add_node_parse(t_node **head, t_node *node);
t_node	*new_node(int type, char **arg);

#endif