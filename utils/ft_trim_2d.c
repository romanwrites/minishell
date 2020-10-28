/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 00:51:06 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/28 20:35:30 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	len_2d(char **ptr)
{
	size_t		i;

	i = 0;
	while (ptr[i])
	{
		i++;
	}
	return (i);
}

char			**ft_trim_2d_cpy(char **arr_2d)
{
	char		**new;
	char		*tmp;
	size_t 		len;
	int			i;

	i = 0;
	len = len_2d(arr_2d);
	new = (char **)malloc(sizeof(char *) * len + 1);
	ft_alloc_check(new);
	while (i < len)
	{
		tmp = ft_strtrim(arr_2d[i], " ");
		ft_alloc_check(tmp);
		new[i] = tmp;
		tmp = NULL;
		i++;
	}
	new[i] = NULL;
	ft_free2d(arr_2d);
	return (new);
}
