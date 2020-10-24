/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 17:15:57 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/24 17:15:58 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool			check_sequence_semi(char c1, char c2)
{
	if (c1 == SEMICOLON && (c2 == SEMICOLON || c2 == PIPE))
		return (1);
	else if (c1 == PIPE && (c2 == PIPE || c2 == SEMICOLON))
		return (1);
	else if (c1 == REDIR_LEFT && c2 == PIPE)
		return (1);
	return (0);
}

_Bool			check_sequence_full(char c1, char c2)
{
	if (c1 == SEMICOLON && (c2 == SEMICOLON || c2 == PIPE))
		return (1);
	else if (c1 == PIPE && (c2 == PIPE || c2 == SEMICOLON))
		return (1);
	else if (c1 == REDIR_LEFT && c2 == PIPE)
		return (1);
	else if (c1 == REDIR_LEFT && c2 == REDIR_LEFT)
		return (1);
	else if (c1 == REDIR_RIGHT && c2 == REDIR_RIGHT)
		return (1);
	else if (c1 == REDIR_RIGHT && c2 == REDIR_LEFT)
		return (1);
	return (0);
}

_Bool			other_conditions(const char *str, int i)
{
	if (!is_open_quote() && i > 0 && !is_backslash_active() \
						&& check_sequence_semi(str[i - 1], str[i]))
		return (1);
	else if (str[i] == REDIR_RIGHT && str[i + 1] == REDIR_RIGHT && \
					str[i + 2] == REDIR_RIGHT)
		return (1);
	return (0);
}

static int		after_quotes(const char *str, int i)
{
	while (str[i++] && is_open_quote())
		set_states(str[i]);
	return (i);
}

_Bool			check_syntax_errors(const char *str)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (str[i])
	{
		set_states(str[i]);
		if (is_open_quote())
			i = after_quotes(str, i) - 1;
		else if (ft_isspace(str[i]))
		{
			j = i - 1;
			while (ft_isspace(str[i]))
				set_states(str[i++]);
			if (str[i] && check_sequence_full(str[j], str[i]))
				return (1);
		}
		else if (other_conditions(str, i))
			return (1);
		i++;
	}
	return (0);
}
