/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 19:09:41 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/24 19:09:42 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool			check_redirs_only(const char *str)
{
	if (!(ft_strcmp(">>", str)) || !(ft_strcmp(">", str)) || \
		!(ft_strcmp("<", str)))
	{
		return (1);
	}
	return (0);
}

_Bool			check_dot_only(const char *str)
{
	if (!(ft_strcmp(".", str)))
	{
		return (1);
	}
	return (0);
}

_Bool			check_syntax_2d(char **ptr)
{
	int			i;

	i = 0;
	while (ptr[i])
	{
		if (check_redirs_only(ptr[i]))
		{
			g_exit = 258;
			print_error(SYNTAX_ERROR);
			return (1);
		}
		else if (check_dot_only(ptr[i]))
		{
			g_exit = 2;
			print_error("bash: .: filename argument required");
			print_error(".: usage: . filename [arguments]");
			return (1);
		}
		i++;
	}
	return (0);
}

_Bool			check_syntax_by_indexes(const char *str)
{
	size_t		l;

	l = ft_strlen(str);
	if (str[0] == PIPE || str[l - 1] == PIPE)
		return (1);
	if (str[0] == SEMICOLON)
		return (1);
	else if (str[l] == REDIR_LEFT && l > 1 && str[l - 1] != BACKSLASH)
		return (1);
	else if (str[l] == REDIR_RIGHT && l > 1 && str[l - 1] != BACKSLASH)
		return (1);
	return (0);
}
