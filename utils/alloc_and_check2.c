/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_and_check2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:28:12 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/30 18:28:42 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*ft_lstnew_kv_n_chk(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	ft_alloc_check(new);
	new->content = content;
	new->next = NULL;
	return (new);
}

char		**ft_split_n_chk(char *str, char c)
{
	char	**ptr;

	ptr = ft_split(str, c);
	ft_alloc_check(ptr);
	return (ptr);
}
