/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:31:59 by ilahyani          #+#    #+#             */
/*   Updated: 2021/11/20 12:07:18 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*new;
	t_list	*tmp;

	tmp = NULL;
	node = lst;
	while (node)
	{
		new = ft_lstnew((*f)(node->content));
		if (!new)
		{
			ft_lstclear(&new, del);
			return (0);
		}
		ft_lstadd_back(&tmp, new);
		node = node->next;
	}
	return (tmp);
}
