/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_and_check2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:28:12 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/30 19:26:17 by lhelper          ###   ########.fr       */
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

char		*ft_strjoin_n_chk(char *s1, char *s2)
{
	char	*ptr;

	ptr = ft_strjoin(s1, s2);
	ft_alloc_check(ptr);
	return (ptr);
}
