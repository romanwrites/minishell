/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 00:49:14 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/27 16:24:25 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_new_lines_over_char(char c, char *str)
{
	int		j;

	j = 0;
	while (str[j])
	{
		set_backslash_state_new(str[j]);
		set_quotes_state_new(str[j]);
		if (str[j] == c && !is_open_quote() && !is_backslash_active())
		{
			str[j] = '\n';
		}
		j++;
	}
}

char		**split_by_char(char c, char *str)
{
	char	**semicolon2d;
//	char	**new_ptr;

	init_globs();
	set_new_lines_over_char(c, str);
	semicolon2d = ft_split(str, '\n');
	reset_newlines(str);
	ft_alloc_check(semicolon2d);
//	new_ptr = ft_trim_2d_cpy(semicolon2d);
	return (semicolon2d);
}
