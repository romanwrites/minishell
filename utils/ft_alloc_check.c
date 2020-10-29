/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 16:34:22 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/27 16:39:12 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_alloc_check(void *ptr)
{
	if (ptr == NULL)
	{
		write(2, "Error!\nOut of memory\n", 21);
		exit(2);
	}
}
