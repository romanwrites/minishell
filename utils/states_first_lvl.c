/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_first_lvl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 19:56:15 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/24 19:56:18 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_backslash_state(t_parse *state_check, char c)
{
	if (c == 92 && !state_check->backslash)
	{
		state_check->backslash_time = 3;
		state_check->backslash = 1;
	}
	else
		state_check->backslash = 0;
	if (state_check->backslash_time)
		state_check->backslash_time--;
}

_Bool		is_backslash_pressed(t_parse *state_check)
{
	if (state_check->backslash_time)
		return (1);
	return (0);
}

void		set_quotes_state(t_parse *state_check, int j, const char *str)
{
	if (str[j] == DOUBLE_QUOTE && \
	!state_check->is_double_quote_open && !state_check->is_single_quote_open)
		state_check->is_double_quote_open = 1;
	else if (str[j] == DOUBLE_QUOTE && \
	state_check->is_double_quote_open && j > 0 && str[j - 1] != BACKSLASH)
		state_check->is_double_quote_open = 0;
	else if (str[j] == SINGLE_QUOTE && \
	!state_check->is_single_quote_open && !state_check->is_double_quote_open)
		state_check->is_single_quote_open = 1;
	else if (str[j] == SINGLE_QUOTE && state_check->is_single_quote_open)
		state_check->is_single_quote_open = 0;
}

_Bool		is_any_quote_open(t_parse *state_check)
{
	if (state_check->is_single_quote_open || state_check->is_double_quote_open)
		return (1);
	return (0);
}
