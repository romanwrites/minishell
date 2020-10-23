/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 00:51:06 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/30 00:51:08 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		len_2d(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
	{
		i++;
	}
	return (i);
}

char		**ft_trim_2d_cpy(char **arr_2d)
{
	char	**new;
	char	*tmp;
	size_t 	len;
	int 	i;

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
	return (new);
}

void		ft_trim_2d(char ***arr_2d)
{
	char	**tmp_2d;
	char 	*tmp;
	int 	i;

	tmp_2d = *(arr_2d);
	tmp = NULL;
	i = 0;
	while (tmp_2d[i])
	{
		tmp = tmp_2d[i];
		tmp_2d[i] = ft_strtrim(tmp, " \t");
		ft_alloc_check(tmp_2d[i]);
		free(tmp);
		tmp = NULL;
		i++;
	}
}