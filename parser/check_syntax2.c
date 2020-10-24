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
		!(ft_strcmp("<", str)) || !(ft_strcmp("<", str)))
	{
		printf("WTF: [%s]\n", str);
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
			return (1);
		i++;
	}
	return (0);
}

_Bool			check_syntax_by_indexes(const char *str)
{
	size_t		len;

	len = ft_strlen(str);
	if (str[0] == PIPE || str[0] == SEMICOLON)
		return (1);
	else if (str[len] == REDIR_LEFT && len > 1 && str[len - 1] != BACKSLASH)
		return (1);
	else if (str[len] == REDIR_RIGHT && len > 1 && str[len - 1] != BACKSLASH)
		return (1);
	return (0);
}
