/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:04:53 by mjlem             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/27 14:15:53 by mjlem            ###   ########.fr       */
=======
/*   Updated: 2022/07/26 22:20:28 by ilahyani         ###   ########.fr       */
>>>>>>> fa34d900a4ec71a3df5084d673f43cc3d0f82ce9
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_list(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("%s--%c\n", tmp->arg, tmp->type);
		tmp = tmp->next;
	}
}

// int	ft_strcmp(char *s1, char *s2)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s1[i] && s2[i] && s1[i] == s2[i])
// 		i++;
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

void	print_list2(t_node *tokens)
{
	t_node	*tmp;
	int		i;

	tmp = tokens;
	i = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
			printf("|%s|", tmp->cmd[i++]);
		printf("--%c\n", tmp->type);
		tmp = tmp->next;
	}
}

int	heredoc_here(int type)
{
	static int	flag = 0;

	if (type == HERE_DOC)
		flag = 1;
	if (type == EXPAND && flag)
	{
		flag = 0;
		return (0);
	}
	else
		return (1);
}

char	*expand_exit_code(char *arg)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;
	int		l;

	i = 0;
	j = 1;
	l = 0;
	tmp = malloc(ft_strlen(arg));
	while (arg[j])
	{
		if (j == 1)
		{
			tmp2 = ft_itoa(g_exit);
			while (tmp2[i])
			{
				tmp[i] = tmp2[l];
				i++;
				l++;
			}
			j++;
		}
		tmp[i] = arg[j];
		j++;
		i++;
	}
	tmp[i] = '\0';
	free(arg);
	return (tmp);
}

t_token *expand_var(t_token *tokens, t_env *list_env)
{

    t_env   *tmp;
	t_token	*mv;

    tmp = list_env;
	mv = tokens;
	while (mv)
	{
		if (heredoc_here(mv->type) && mv->type == EXPAND)
		{
			if (mv->arg[1] == '?')
				mv->arg = expand_exit_code(mv->arg);
			else
			{	
				while (tmp)
				{
					if (!ft_strcmp(mv->arg+1, tmp->var))
					{
						free(mv->arg);
						mv->arg = ft_strdup(tmp->value);
						break ;
					}
					tmp = tmp->next;
				}
				if (!tmp)
				{
					free(mv->arg);
					mv->arg = ft_strdup("");
				}
			}
			tmp = list_env;
		}
		mv = mv->next;
	}
	return (tokens);
}

char	**add_to_table(char **tmp2, char *tmp1)
{
	int		i;
	char	**tmp;
	int		j;

	i = 0;
	j = 0;
	if (!tmp1)
	{
		tmp = malloc(sizeof(char *));
		tmp[0] = NULL;
	}	
	if (!tmp2)
		tmp = malloc(sizeof(char *) * 2);
	else
	{
		while (tmp2[i])
			i++;
		tmp = malloc (sizeof(char *) * (i + 2));
		i = -1;
		while (tmp2[++i])
			tmp[i] = ft_strdup(tmp2[i]);
		while (tmp2[j])
			free(tmp2[j++]);
		free(tmp2);
	}
	tmp[i++] = ft_strdup(tmp1);
	tmp[i] = NULL;
	return (tmp);
}

void	word(t_token **tokens, t_node **line)
{
	char	*tmp;
	char	**tmp_2d;

	tmp = NULL;
	tmp_2d = NULL;
	while ((*tokens) && ((*tokens)->type == WORD || (*tokens)->type == W_SPACE
			|| (*tokens)->type == EXPAND || (*tokens)->type == SQ_STR))
	{
		tmp = ft_strjoin(tmp, (*tokens)->arg);
		(*tokens) = (*tokens)->next;
		if (!(*tokens) || (*tokens)->type == W_SPACE
			|| (*tokens)->type == EXPAND)
		{
			if ((*tokens) && (*tokens)->type == W_SPACE)
				(*tokens) = (*tokens)->next;
			tmp_2d = add_to_table(tmp_2d, tmp);
			free(tmp);
			tmp = NULL;
		}
	}
	tmp_2d = add_to_table(tmp_2d, tmp);
	add_node_parse(line, new_node(WORD, tmp_2d));
} 

void	parse_pipe(t_token **tokens, t_node **line)
{
	add_node_parse(line, new_node(PIPE, add_to_table(NULL, NULL)));
	(*tokens) = (*tokens)->next;
}

void	parse_re(t_node **line, t_token **tokens)
{
	int		type;
	char	*tmp;
	char	**tmp2;

	tmp = NULL;
	tmp2 = NULL;
	type = (*tokens)->type;
	(*tokens) = (*tokens)->next;
	if ((*tokens)->type == W_SPACE)
		(*tokens) = (*tokens)->next;
	if ((*tokens) && ((*tokens)->type == WORD || (*tokens)->type == EXPAND || (*tokens)->type == SQ_STR))
	{
		while ((*tokens) && ((*tokens)->type == WORD || (*tokens)->type == EXPAND || (*tokens)->type == SQ_STR))
		{
			tmp = ft_strjoin(tmp, (*tokens)->arg);
			(*tokens) = (*tokens)->next;
			// if (!(*tokens) || (*tokens)->type == EXPAND || (*tokens)->type == SQ_STR)
			// {
			// 	tmp2 = add_to_table(tmp2, tmp);
			// 	free(tmp);
			// 	tmp = NULL;
			// }
		}
		tmp2 = add_to_table(tmp2, tmp);
		add_node_parse(line, new_node(type, tmp2));
	}
}

void	parse_heredoc(t_node **line, t_token **tokens)
{
	char	*tmp;
	char	**tmp2;
	int		type;

	tmp = NULL;
	tmp2 = NULL;
	type = (*tokens)->type;
	(*tokens) = (*tokens)->next;
	if ((*tokens)->type == W_SPACE)
		(*tokens) = (*tokens)->next;
	if ((*tokens) && ((*tokens)->type == WORD || (*tokens)->type == EXPAND || (*tokens)->type == SQ_STR))
	{
		while ((*tokens) && ((*tokens)->type == WORD || (*tokens)->type == EXPAND || (*tokens)->type == SQ_STR))
		{
			tmp = ft_strjoin(tmp, (*tokens)->arg);
			(*tokens) = (*tokens)->next;
		}
		tmp2 = add_to_table(tmp2, tmp);
		add_node_parse(line, new_node(type, tmp2));
	}
}

t_node	*parse(t_token **tokens)
{
	t_node	*line;

	line = NULL;
	while ((*tokens))
	{
		if ((*tokens)->type == WORD || (*tokens)->type == EXPAND || (*tokens)->type == SQ_STR)
			word(tokens, &line);
		else if ((*tokens)->type == PIPE)
			parse_pipe(tokens, &line);
		else if ((*tokens)->type == OUT_REDIR || (*tokens)->type == RE_ADD
			|| (*tokens)->type == IN_REDIR)
			parse_re(&line, tokens);
		else if ((*tokens)->type == W_SPACE)
			(*tokens) = (*tokens)->next;
		else if ((*tokens)->type == HERE_DOC)
			parse_heredoc(&line, tokens);
	}
	return (line);
}

t_node	*move_node(t_node *node, t_node *head, t_node **origin)
{
	t_node	*tmp;
	t_node	*tmp2;
	t_node	*tmp3;

	tmp = head;
	tmp3 = (*origin);
	if ((*origin)->type != WORD)
	{
		(*origin)->next = node->next;
		node->next = (*origin);
		(*origin) = node;
		return (head);
	}
	else if (node != head && head->type == WORD)
	{
		while (tmp && tmp->next && tmp->next->type == WORD)
			tmp = tmp->next;
		tmp2 = tmp;
		while (tmp2 && tmp2->next != node)
			tmp2 = tmp2->next;
		tmp2->next = node->next;
		node->next = tmp->next;
		tmp->next = node;	
	}
	else if (head->type != WORD)
	{
		while (tmp3->next != head)
			tmp3 = tmp3->next;
		tmp3->next = node;
		head->next = node->next;
		node->next = head;
		return (node);
	}
	return (head);
}

char	**join_2d(char **arg1, char **arg2)
{
	int		i;
	int		j;
	char	**tmp;
	
	i = 0;
	j = 0;
	while (arg1[i])
		i++;
	while (arg2[j])
		j++;
	tmp = malloc (sizeof(char *) * (j + i + 1));
	i = -1;
	while (arg1[++i])
		tmp[i] = ft_strdup(arg1[i]);
	j = 0;
	while (arg2[j])
	{
		tmp[i] = ft_strdup(arg2[j++]);
		i++;
	}
	tmp[i] = NULL;
	// free_tab(arg1);
	// free_tab(arg2);
	/*free arg1 and arg2*/
	return (tmp);
}

t_node *join_words(t_node *list)
{
	t_node	*tmp;
	t_node	*tof;
	int		i;
	char	*tmp1;

	tmp = list;
	i = 0;
	tmp1 = NULL;
	// print_list2(list);
	while (tmp)
	{
		if (tmp && tmp->next && tmp->type == WORD && tmp->next->type == WORD)
		{
			tmp->cmd = join_2d(tmp->cmd, tmp->next->cmd);
			tof = tmp->next;
			tmp->next = tmp->next->next;
			free(tof);
		}
		else if (tmp && (tmp->type == OUT_REDIR || tmp->type == RE_ADD || tmp->type == IN_REDIR))
		{
			if (tmp->cmd[0] && tmp->cmd[1])
			{
				while (tmp->cmd[i])
					tmp1 = ft_strjoin(tmp1, tmp->cmd[i++]);
				free_tab(tmp->cmd);
				tmp->cmd = add_to_table(NULL, tmp1);
			}
			tmp = tmp->next;
			i = 0;
		}
		else
			tmp = tmp->next;
	}
	return (list);
}

t_node	*adjuste_list(t_node *list)
{
	t_node	*tmp;
	t_node *tmp2;

	tmp = list;
	tmp2 = list;
	while (tmp)
	{
		while (tmp && tmp->type != PIPE)
		{
			if (tmp->type == WORD)
			{
				tmp2 = move_node(tmp, tmp2, &list);
			}
			tmp = tmp->next;
		}
		if(!tmp)  
			break ;
		tmp = tmp->next;
		tmp2 = tmp;
	}
	list = join_words(list);
	return (list);
}

t_node	*parser(char *line, t_env *lst_env)
{
	t_token	*tokens;
	t_node	*list;
	t_token	*tmp;

	list = NULL;
	tokens = lexer(line);
	if (!tokens)
	{
		printf("Error\n");
		return (list);
	}
	tmp = tokens;
	if (pipeline(&tmp) == 1)
	{
		tokens = expand_var(tokens, lst_env);
		// print_list(tokens);
		list = parse(&tokens);
		// print_list2(list);
		list = adjuste_list(list);
		// printf("------------------------\n");
<<<<<<< HEAD
		print_list2(list);
=======
		//  print_list2(list);
>>>>>>> fa34d900a4ec71a3df5084d673f43cc3d0f82ce9
		// printf("------------------------\n");
	}
	return (list);
}
<<<<<<< HEAD
=======

/*$? && $??*/
>>>>>>> fa34d900a4ec71a3df5084d673f43cc3d0f82ce9
