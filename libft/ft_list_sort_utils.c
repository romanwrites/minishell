/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:01:45 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/29 18:01:46 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		max_len(size_t len_a, size_t len_b)
{
	if (len_a > len_b)
		return (len_a);
	return (len_b);
}

int			first_swap(t_list **iter1, t_list **iter2)
{
	struct s_list *tmp;

	tmp = NULL;
	tmp = *iter1;
	(*iter1)->next = (*iter2)->next;
	(*iter2)->next = tmp;
	return (2);
}

int			swap(t_list **iter0, t_list **iter1, t_list **iter2)
{
	struct s_list *tmp;

	tmp = NULL;
	tmp = (*iter0)->next;
	(*iter0)->next = (*iter1)->next;
	(*iter1)->next = (*iter2)->next;
	(*iter2)->next = tmp;
	return (1);
}
