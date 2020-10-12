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