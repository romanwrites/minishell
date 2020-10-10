/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 05:53:19 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/07 05:53:29 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool		is_valid_syntax(char pre, char cur, char next)
{
	if (cur == '|' && (pre == '|' || next == '|' || pre == '<' ||  pre == '>' ||  next == '<' || next == '>' || !pre || !next))
		return (0);
	else if (cur == '>' && (pre == '|' || next == '|' || pre == '<' || next == '<' || !pre || !next))
		return (0);
	else if (cur == '<' && (pre == '|' || next == '|' || pre == '>' || next == '>' || !pre || !next))
		return (0);
	return (1);
}

_Bool		is_redir_or_pipe(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

void		set_nl_cpy(char **str, int i)
{
	char 	*tmp;
	char	*new;

	tmp = *(str);
	new = malloc(ft_strlen(tmp) + 2);
	ft_alloc_check(new);
	ft_memcpy(new, tmp, i);
	new[i] = '\n';
	ft_memcpy(new + i + 1, tmp + i, ft_strlen(tmp) - i + 2);
	free(tmp);
	*(str) = new;
}

char		**split_command(t_mshell *sv, char *str)
{
	size_t 	i;
	char	**split_by_command;

	i = 0;
	while (str[i])
	{
		set_backslash_state(sv->state, str[i], i);
		set_quotes_state(sv, sv->state, i, str);
		if (is_any_quote_open(sv->state))
		{
			i++;
			continue ;
		}
		if ((str[i] == ' ' || str[i] == '\t') && !is_backslash_pressed(sv->state))
			str[i] = '\n';
		else if (i > 0 && (str[i] == '|' || str[i] == '<' || str[i] == '>') && \
				(is_valid_syntax(str[i - 1], str[i], str[i + 1])) && \
				(str[i - 1] != '\n'))
        {
			set_nl_cpy(&str, i);
			i++;
		}
		else if (i > 0 && str[i] != ' ' && str[i] != 34 && str[i] != 39 && is_redir_or_pipe(str[i - 1]))
        {
            set_nl_cpy(&str, i);
            i++;
        }
		i++;
	}
	split_by_command = ft_split(str, '\n');
	ft_alloc_check(split_by_command);
	return (split_by_command);
}