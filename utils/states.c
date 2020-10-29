/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 17:59:16 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/28 20:44:45 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init_globs()
{
	g_dquote = 0;
	g_squote = 0;
	g_backslash = 0;
	g_backslash_time = 0;
}

_Bool		is_open_quote()
{
	return (g_squote != g_dquote);
}

void		set_quotes_state_new(char c)
{
	if (c == DOUBLE_QUOTE && !is_open_quote())
		g_dquote = 1;
	else if (c == DOUBLE_QUOTE && g_dquote)
		g_dquote = 0;
	else if (c == SINGLE_QUOTE && !is_open_quote())
		g_squote = 1;
	else if (c == SINGLE_QUOTE && g_squote)
		g_squote = 0;
}

_Bool		is_backslash_active()
{
	if (g_backslash_time)
		return (1);
	return (0);
}

void		set_backslash_state_new(char c)
{
	if (c == BACKSLASH && !g_backslash && !g_squote)
	{
		g_backslash_time = 3;
		g_backslash = 1;
	}
	else
		g_backslash = 0;
	if (g_backslash_time)
		g_backslash_time--;
}
