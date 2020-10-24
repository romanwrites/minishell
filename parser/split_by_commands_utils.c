/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_commands_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 17:07:38 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/24 17:07:39 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool		is_pipe_or_single_redir(const char *str, int i)
{
	return ((str[i] == PIPE || str[i] == REDIR_LEFT || \
		(str[i] == REDIR_RIGHT && str[i + 1] != REDIR_RIGHT && \
		str[i - 1] != REDIR_RIGHT)) && \
				(str[i - 1] != NEWLINE));
}

_Bool		is_double_redir(const char *str, int i)
{
	return (str[i - 1] != NEWLINE && \
			(str[i] == REDIR_RIGHT && str[i + 1] == REDIR_RIGHT));
}

_Bool		is_after_redir(const char *str, int i)
{
	if (str[i] != REDIR_RIGHT && str[i] != REDIR_LEFT)
	{
		if (str[i - 1] == REDIR_RIGHT && str[i - 2] == REDIR_RIGHT)
			return (1);
		if (str[i - 1] == REDIR_RIGHT && str[i - 2] == NEWLINE)
			return (1);
		if (str[i - 1] == REDIR_LEFT && str[i - 2] == NEWLINE)
			return (1);
	}
	return (0);
}

_Bool		is_after_redir_or_pipe(const char *str, int i)
{
	return (str[i] != ' ' && str[i] != DOUBLE_QUOTE && \
		str[i] != SINGLE_QUOTE && \
		(str[i - 1] == PIPE || str[i - 1] == REDIR_LEFT));
}

_Bool		is_after_redir_semi_check(const char *str, int i)
{
	return (str[i] != REDIR_RIGHT && str[i] != REDIR_LEFT && \
		(str[i - 1] == REDIR_LEFT || str[i - 1] == REDIR_RIGHT));
}
