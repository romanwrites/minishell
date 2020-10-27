/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:09:21 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/24 15:09:22 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		get_dollars_end(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == '$')
	{
		i++;
	}
	return (i);
}

int			get_env_from_str(const char *str)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isalpha(str[i]))
			break ;
		i++;
	}
	return (i);
}
