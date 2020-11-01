/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:41:02 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/28 19:43:04 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			get_several_dollars(t_open_q *o, int i)
{
	int			j;

	j = get_dollars_end(o->str + i);
	if (i > o->save + 2 && is_backslash_active())
	{
		o->append_this = ft_substr_and_chk(o->str, o->save, i - o->save - 1);
		append_line(&o->new_line, &o->append_this);
	}
	else if (i > o->save + 2 && !is_backslash_active())
	{
		o->append_this = ft_substr_and_chk(o->str, o->save, i - o->save);
		append_line(&o->new_line, &o->append_this);
	}
	o->append_this = ft_substr_and_chk(o->str, i, j);
	append_line(&o->new_line, &o->append_this);
	i += j;
	o->save = i + 2;
	o->i = i;
}

void			append_dollar_after_backslash(t_open_q *o, int i, int j)
{
	if (i > o->save + 2)
	{
		o->append_this = ft_substr_and_chk(o->str, o->save, i - o->save - 1);
		append_line(&o->new_line, &o->append_this);
	}
	o->append_this = ft_substr_and_chk(o->str, i, j);
}

void			get_env_val(t_open_q *o, int i, int j)
{
	char		*value_to_check;
	char		*env_value;

	value_to_check = NULL;
	env_value = NULL;
	if (i > o->save + 1) //was >=
	{
		o->append_this = ft_substr_and_chk(o->str, o->save, i - o->save);
		append_line(&o->new_line, &o->append_this);
	}
	if (j == 2)
		value_to_check = ft_strdup_and_check("");
	else
		value_to_check = ft_substr_and_chk(o->str, i + 1, j > 1 ? j - 1 : j);
	env_value = get_envar(value_to_check);
	if (!env_value)
		o->append_this = ft_strdup_and_check("");
	else
	{
		o->append_this = ft_strdup_and_check(env_value);
	}
	if (env_value)
		free_and_null(&env_value);
	free_and_null(&value_to_check);
}

void			handle_dollar(t_open_q *o, int i)
{
	int			j;
	char		*str;

	str = o->str;
	if (str[i + 1] == '$')
	{
		get_several_dollars(o, i);
		return ;
	}
	else if (ft_isdigit(str[i + 1]))
	{
		i += 2;
		o->i = i;
		o->save += 2;
		return ;
	}
	j = get_env_from_str(str + i);
	if (is_backslash_active())
		append_dollar_after_backslash(o, i, j);
	else
		get_env_val(o, i, j);
	append_line(&o->new_line, &o->append_this);
	i += j > 1 ? j - 1 : j;
	o->save = i + 1;
	o->i = ++i;
}
