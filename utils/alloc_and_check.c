/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_and_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:39:35 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/24 15:39:36 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_itoa_and_chk(int n)
{
	char	*res;

	res = ft_itoa(n);
	ft_alloc_check(res);
	return (res);
}

char		*ft_substr_and_chk(char const *str, unsigned int start, size_t len)
{
	char	*new_str;

	new_str = ft_substr(str, start, len);
	ft_alloc_check(new_str);
	return (new_str);
}

void		*ft_strdup_and_check(const char *str)
{
	char	*new_str;

	new_str = ft_strdup(str);
	ft_alloc_check(new_str);
	return (new_str);
}

t_list		*ft_lstnew_n_chk(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	ft_alloc_check(new);
	new->content = content;
	new->next = NULL;
	return (new);
}

void		*malloc_n_chk(size_t size)
{
	void	*ret;

	ret = malloc(size);
	ft_alloc_check(ret);
	return (ret);
}
