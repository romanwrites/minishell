/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:29:42 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/10 18:25:08 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_nodes(t_list **begin_list)
{
	t_list	*iter0;
	int		i;

	i = 0;
	iter0 = *begin_list;
	while (iter0)
	{
		iter0 = iter0->next;
		i++;
	}
	return (i);
}

static void	init_iter(t_list **iter0, t_list **iter1, t_list **iter2, \
						t_list **begin_list)
{
	*iter0 = NULL;
	*iter1 = *begin_list;
	*iter2 = (*iter1)->next;
}

static void	check_swp(t_list **iter0, t_list **iter1, t_list **iter2, int swp)
{
	if (!swp)
	{
		*iter0 = *iter1;
		*iter1 = (*iter1)->next;
		*iter2 = (*iter2)->next;
	}
	else
	{
		*iter0 = *iter2;
		*iter1 = (*iter2)->next;
		*iter2 = (*iter1)->next;
	}
}

static int	make_swap(t_list **iter0, t_list **iter1, t_list **iter2)
{
	int		swp;

	swp = 0;
	if (!*iter0)
		swp = first_swap(iter1, iter2);
	else
		swp = swap(iter0, iter1, iter2);
	return (swp);
}

void		ft_list_sort(t_list **begin_list, int (*cmp)())
{
	int		i;
	int		swp;
	t_list	*iter0;
	t_list	*iter1;
	t_list	*iter2;

	if (!(*begin_list) || !(*begin_list)->next)
		return ;
	swp = 0;
	i = count_nodes(begin_list);
	while (i-- > 1)
	{
		init_iter(&iter0, &iter1, &iter2, begin_list);
		while (iter2)
		{
			if (cmp(iter1->content, iter2->content) > 0)
				swp = make_swap(&iter0, &iter1, &iter2);
			check_swp(&iter0, &iter1, &iter2, swp);
			if (swp == 2)
				*begin_list = iter0;
			swp = 0;
		}
	}
}
