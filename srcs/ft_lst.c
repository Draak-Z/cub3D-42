/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:50:31 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 12:38:17 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **alst, t_list *new, t_data *data)
{
	t_list	*last;

	if (!new)
		data->error = 10;
	if ((last = ft_lstlast(*alst)) != NULL)
		last->next = new;
	else
		*alst = new;
}

void	ft_lstclear(t_list **lst)
{
	t_list	*current;
	t_list	*tmp;

	current = *lst;
	while (current)
	{
		free(current->content);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*lst = NULL;
}

int		ft_lstsize(t_list *lst)
{
	int c;

	c = 0;
	while (lst)
	{
		lst = lst->next;
		c++;
	}
	return (c);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	if (!(elem = malloc(sizeof(t_list))))
		return (NULL);
	elem->content = content;
	elem->next = 0;
	return (elem);
}
