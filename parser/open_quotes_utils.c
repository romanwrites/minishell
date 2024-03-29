/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quotes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:41:05 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/28 19:43:04 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool			is_env_val_after_dollar(char c)
{
	return (ft_isdigit(c) || ft_isalpha(c) || c == DOLLAR || c == '?');
}

char			*just_tilde(t_open_q *o, int i)
{
	char		*env_value;

	env_value = get_envar("~");
	if (!env_value)
		o->append_this = ft_strdup_and_check("");
	else
	{
		o->append_this = ft_strdup_and_check(env_value);
	}
	append_line(&o->new_line, &o->append_this);
	o->save = i + 1;
	free_and_null(&env_value);
	return (o->new_line);
}

void			append_tilda(t_open_q *o, size_t i)
{
	char		*val;
	char		*tmp;

	val = get_envar("~");
	tmp = o->new_line;
	o->new_line = ft_strjoin_n_chk(tmp, val);
	free(tmp);
	free(val);
	o->save = i + 1;
	o->is_tilda = 1;
}
