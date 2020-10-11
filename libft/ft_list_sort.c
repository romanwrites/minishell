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

size_t		max_len(size_t len_a, size_t len_b)
{
	if (len_a > len_b)
		return(len_a);
	return(len_b);
}

int		first_swap(t_list **iter1, t_list **iter2)
{
	struct s_list *tmp = NULL;

	tmp = *iter1;
	(*iter1)->next = (*iter2)->next;
	(*iter2)->next = tmp;
	return 2;
}

int		swap(t_list **iter0, t_list **iter1, t_list **iter2)
{
	struct s_list *tmp = NULL;

	tmp = (*iter0)->next;
	(*iter0)->next = (*iter1)->next;
	(*iter1)->next = (*iter2)->next;
	(*iter2)->next = tmp;
	return 1;
}

void		ft_list_sort(t_list **begin_list, int (*cmp)())
{
	int i = 0;
	int swp = 0;
	t_list *iter0;
	t_list *iter1;
	t_list *iter2;

	if (!(*begin_list) || !(*begin_list)->next)
		return ;
	iter0 = *begin_list;
	while (iter0)
	{
		iter0 = iter0->next;
		i++;
	}
	while (i-- > 1)
	{
		iter0 = NULL;
		iter1 = *begin_list;
		iter2 = iter1->next;
		while (iter2)
		{
			if(cmp(iter1->content, iter2->content) > 0)
			{
				if (!iter0)
					swp = first_swap(&iter1, &iter2);
				else
					swp = swap(&iter0, &iter1, &iter2);
			}
			if (!swp)
			{
				iter0 = iter1;
				iter1 = iter1->next;
				iter2 = iter2->next;
			}
			else
			{
				iter0 = iter2;
				iter1 = iter2->next;
				iter2 = iter1->next;
			}
			if (swp == 2)
				*begin_list = iter0;
			swp = 0;
		}
	}
}
