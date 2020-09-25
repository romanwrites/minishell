/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 00:26:07 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/25 14:41:58 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_memcmp(void *s1, void *s2, size_t n)
{
	char *st1;
	char *st2;

	st1 = s1;
	st2 = s2;
	while (n > 0)
	{
		if (*st1 != *st2)
			return ((unsigned char)*st1 - (unsigned char)*st2);
		st1++;
		st2++;
		n--;
	}
	return (0);
}
