/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 17:38:07 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/27 15:07:41 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool		find_next_double_q_mark(t_mshell *sv)
{
	int		j;

	j = 0;
	while (sv->content[j])
	{
		if (sv->content[j] == '"' && sv->content[j - 1] != '\\')
		{
			sv->i = j;
			return (1);
		}
		j++;
	}
	return (0);
}

void		split_sh(t_mshell *sv)
{
	sv->i = 0;
	_Bool d_q_mark_flag = 0;
	int tokens = 0;

	while (sv->content[sv->i])
	{
		if (sv->content[sv->i] == '"' && !d_q_mark_flag)
		{
			d_q_mark_flag = 1;
			if (find_next_double_q_mark(sv))
			{
				tokens += 1;
				d_q_mark_flag = 0;
				continue ;
			}
		}

		sv->i++;
	}
}

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