/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2d_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 00:20:50 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/28 20:37:01 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_2d_array(char **arr2d)
{
	int		i;

	i = 0;
	if (arr2d)
	{
		while(arr2d[i])
		{
			ft_putendl_fd(arr2d[i], 1);
			i++;
		}
		ft_putendl_fd("(null)", 1);
	}
}
