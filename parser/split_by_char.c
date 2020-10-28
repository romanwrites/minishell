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

void		set_new_lines_over_char(char c, char *str, t_mshell *sv)
{
	int		j;

	j = 0;
	while (str[j])
	{
		set_backslash_state(sv->state, str[j]);
		set_quotes_state(sv->state, j, str);
		if (str[j] == c && !is_any_quote_open(sv->state) && \
							!is_backslash_pressed(sv->state))
		{
			str[j] = '\n';
		}
		j++;
	}
}

char		**split_by_char(char c, char *str, t_mshell *sv)
{
	char	**semicolon2d;
	char	**new_ptr;

	set_new_lines_over_char(c, str, sv);
	semicolon2d = ft_split(str, '\n');
	reset_newlines(str);
	ft_alloc_check(semicolon2d);
	new_ptr = ft_trim_2d_cpy(semicolon2d);
	return (new_ptr);
}
