/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 17:38:07 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/29 21:47:57 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool		find_next_double_q_mark(t_mshell *sv, char c)
{
	int		j;

	j = 0;
	while (sv->content[j])
	{
		if ((c == 34 && sv->content[j] == 34 && sv->content[j - 1] != 92)
			|| (c == 39 && sv->content[j] == 39))
		{
			sv->i = j;
			return (1);
		}
		j++;
	}
	return (0);
}

int			count_tokens(t_mshell *sv)
{
	sv->i = 0;
	_Bool	double_quot_mark_flag = 0;
	_Bool	solo_quot_mark_flag = 0;
	int		tokens = 0;

	while (sv->content[sv->i])
	{
		if (sv->content[sv->i] == 34 && !double_quot_mark_flag)
		{
			double_quot_mark_flag = 1;
			if (find_next_double_q_mark(sv, sv->content[sv->i]))
			{
				tokens += 1;
				double_quot_mark_flag = 0;
				continue ;
			}
		}
		if (sv->content[sv->i] == 39 && !solo_quot_mark_flag)
		{
			solo_quot_mark_flag = 1;
			if (find_next_double_q_mark(sv, sv->content[sv->i]))
			{
				tokens += 1;
				solo_quot_mark_flag = 0;
				continue ;
			}
		}
		sv->i++;
	}
	return (tokens);
}

void		split_sh(t_mshell *sv)
{
	int		tokens = count_tokens(sv);


void		parse_start(t_mshell *sv)
{
	char	*tmp;

	tmp = sv->content;
	sv->content = ft_strtrim(tmp, " \t");
	ft_alloc_check(sv->content);
	free(tmp);
	tmp = NULL;
	printf("%s\n", sv->content);
	split_sh(sv);

}