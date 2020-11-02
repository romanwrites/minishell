/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quotes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:41:08 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/28 19:43:04 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static _Bool	process_open_quotes(t_open_q *o, int i)
{
	set_states(o->str[i]);
	if (o->str[i] == BACKSLASH && g_dquote && \
					ft_strchr(o->tab, o->str[i + 1]))
	{
		i++;
		chr_join(&o->new_line, o->str[i]);
		o->save = i;
		set_states(o->str[i]);
	}
	else if (o->str[i] == DOLLAR && g_dquote && \
							is_env_val_after_dollar(o->str[i + 1]))
	{
		handle_dollar(o, i);
		return (1);
	}
	else if (is_open_quote())
	{
		o->append_this = ft_substr_and_chk(o->str, i, 1);
		append_line(&o->new_line, &o->append_this);
		o->save = i;
	}
	o->i = i;
	return (0);
}

static void		append_chr_and_save(t_open_q *o, int i)
{
	chr_join(&o->new_line, o->str[i]);
	o->save = i + 1;
}

static void		handle_open_quotes(t_open_q *o, int i)
{
	o->save = i;
	o->i = i + 1;
	while (is_open_quote() && o->str[o->i])
	{
		if (process_open_quotes(o, o->i))
			continue ;
		o->i++;
	}
	o->save = o->i; // was + 1
}

static void		join_open_quotes(t_open_q *o, int i)
{
	i++;
	chr_join(&o->new_line, o->str[i]);
	o->save = i + 1;
	set_backslash_state_new(o->str[i]);
}

char			*open_quotes_str(t_open_q *o, size_t i)
{
	while (o->str[i])
	{
		set_states(o->str[i]);
		if (is_backslash_active() && !is_open_quote())
			join_open_quotes(o, i++);
		else if (o->str[i] == DOLLAR && is_env_val_after_dollar(o->str[i + 1]) \
				&& !is_open_quote())
		{
			handle_dollar(o, i);
			i = o->i;
			continue ;
		}
		else if (is_open_quote())
		{
			handle_open_quotes(o, i);
			i = o->i;
			continue ;
		}
		else if (i == 0 && o->str[i] == '~' && !o->str[i + 1])
			return (just_tilde(o, i));
		else
			append_chr_and_save(o, i);
		i++;
	}
	return (o->new_line);
}
