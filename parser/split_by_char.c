/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 00:49:14 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/30 00:49:17 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_backslash_state(t_parse *state_check, char c, int j)
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

void		set_quotes_state(t_mshell *sv, t_parse *state_check, int j, char *str)
{
	if (str[j] == 34 && !state_check->is_double_quote_open)
		state_check->is_double_quote_open = 1;
	else if (str[j] == 34 && state_check->is_double_quote_open && j > 0 && str[j - 1] != 92)
		state_check->is_double_quote_open = 0;
	else if (str[j] == 39 && !state_check->is_single_quote_open)
		state_check->is_single_quote_open = 1;
	else if (str[j] == 39 && state_check->is_single_quote_open)
		state_check->is_single_quote_open = 0;
}

_Bool		is_any_quote_open(t_parse *state_check)
{
	if (state_check->is_single_quote_open || state_check->is_double_quote_open)
		return (1);
	return (0);
}

void		set_new_lines_over_char(t_mshell *sv, char c, char *str)
{
	int		j = 0;

	while (str[j])
	{
		set_backslash_state(sv->state, str[j], j);
		set_quotes_state(sv, sv->state, j, str);
		if (str[j] == c && !is_any_quote_open(sv->state) && !is_backslash_pressed(sv->state))
		{
			if (str[j + 1] == c)
			{
				exit_error_message("bash: syntax error near unexpected token `;;'"); // set 258
				return ; //debug
			}

			str[j] = '\n';
		}
		if (j > 0 && str[j] == c && str[j - 1] == '\n')
		{
			exit_error_message("bash: syntax error near unexpected token `;;'"); //edit error message with prompt and set 258
			return ; //debug
		}
		if (j == 0 && str[j] == c)
		{
			exit_error_message("bash: syntax error near unexpected token `;'"); //258
			return ; //debug
		}
		j++;
	}
}

char		**split_by_char(t_mshell *sv, char c, char *str)
{
	char	**semicolon2d;

	set_new_lines_over_char(sv, c, str);
	semicolon2d = ft_split(str, '\n');
	ft_alloc_check(semicolon2d);
	return (semicolon2d);
}
