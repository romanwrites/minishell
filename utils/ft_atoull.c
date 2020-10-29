/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:13:20 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/28 20:34:23 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				ft_isspace_atoi(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' ||
		c == '\r' || c == '\v' || c == '\f')
		return (1);
	else
		return (0);
}

unsigned long long		ft_atoull(char *str, int *minus)
{
	int i;
	unsigned long long	num;

	i = 0;
	num = 0;
	while (ft_isspace_atoi(str[i]))
		i = i + 1;
	if (str[i] == '-')
		*minus = 1;
	if (str[i] == '-' || str[i] == '+')
		i = i + 1;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + str[i] - '0';
		i = i + 1;
	}
	return (num);
}
