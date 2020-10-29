/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:03:10 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/28 21:03:13 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*gnl_strjoin_free_null_ret(char *s1_holder)
{
	free(s1_holder);
	return (NULL);
}

_Bool		write_b_b(void)
{
	write(0, "  \b\b", 4);
	return (1);
}

void		process_g_input(void)
{
	if (g_input)
		free_and_null(&g_input);
}

int			process_nl(char *newline_ptr)
{
	*newline_ptr = '\0';
	return (0);
}
