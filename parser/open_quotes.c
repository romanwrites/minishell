/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:22:57 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/20 16:22:58 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool		is_env_val_after_dollar(char c)
{
	return (ft_isdigit(c) || ft_isalpha(c) || c == DOLLAR);
}

void		free_and_null(char **str)
{
	free(*str);
	*str = NULL;
}

void		get_several_dollars(t_open_q *o, int i)
{
	int		j;

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
	o->i = ++i;
}

void		append_dollar_after_backslash(t_open_q *o, int i, int j)
{
	if (i > o->save + 2)
	{
		o->append_this = ft_substr_and_chk(o->str, o->save, i - o->save - 1);
		append_line(&o->new_line, &o->append_this);
	}
	o->append_this = ft_substr_and_chk(o->str, i, j);
}

void		get_env_val(t_open_q *o, int i, int j)
{
	char	*value_to_check;
	char	*env_value;

	value_to_check = NULL;
	env_value = NULL;
	if (i >= o->save + 1)
	{
		o->append_this = ft_substr_and_chk(o->str, o->save, i - o->save);
		append_line(&o->new_line, &o->append_this);
	}
	if (j == 2)
		value_to_check = ft_strdup_and_check("");
	else
		value_to_check = ft_substr_and_chk(o->str, i + 1, j - 1);
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

void		handle_dollar(t_open_q *o, int i)
{
	int		j;
	char	*str;

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
	i += j - 1;
	o->save = i + 1;
	o->i = ++i;
}

void		chr_join(char **str, char c)
{
	char	append[2];
	char 	*new_str;

	append[0] = c;
	append[1] = '\0';
	new_str = ft_strjoin(*str, append);
	free(*str);
	*str = new_str;
}

char 		*just_tilde(t_open_q *o, int i)
{
	char	*env_value;

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

char		*open_quotes_str(t_open_q	*o)
{
	size_t 	i;
	size_t 	j;
	char 	*str;
	char	*value_to_check;
	char 	*env_value;

	i = 0;
	j = 0;
	str = o->str;
	env_value = NULL;
	value_to_check = NULL;
	while (str[i])
	{
		set_states(str[i]);
		if (is_backslash_active() && !is_open_quote())
		{
			i++;
			chr_join(&o->new_line, str[i]);
			o->save = i + 1;
			set_backslash_state_new(str[i]);
		}
		else if (str[i] == DOLLAR && is_env_val_after_dollar(str[i + 1]) && !is_open_quote())
		{
			handle_dollar(o, i);
			i = o->i;
			continue ;
		}
		else if (is_open_quote())
		{
			o->save = i;
			while (is_open_quote() && str[++i])
			{
				set_states(str[i]);
				if (str[i] == BACKSLASH && g_dquote && ft_strchr(o->tab, str[i + 1]))
				{
					i++;
					o->append_this = ft_strdup_and_check(" ");
					o->append_this[0] = str[i];
					append_line(&o->new_line, &o->append_this);
					o->save = i;
					set_states(str[i]);
				}
				else if (str[i] == DOLLAR && g_dquote && is_env_val_after_dollar(str[i + 1]))
				{
					handle_dollar(o, i);
					i = o->i;
					continue ;
				}
				else if (is_open_quote())
				{
					o->append_this = ft_substr_and_chk(str, i, 1);
					append_line(&o->new_line, &o->append_this);
					o->save = i;
				}
			}
			o->save = i + 1;
		}
		else if (i == 0 && str[i] == '~' && !str[i + 1])
		{
			return (just_tilde(o, i));
		}
		else
		{
			chr_join(&o->new_line, str[i]);
			o->save = i + 1;
		}
		i++;
	}
	return (o->new_line);
}

void		set_token_flag(t_token *token, char *str)
{
	if (((str[0] == REDIR_RIGHT || str[0] == REDIR_LEFT) && \
		!str[1]) || !(ft_strcmp(str, REDIR_RIGHT_DOUBLE)))
	{
		token->is_diff = 1;
	}
	else
		token->is_diff = 0;
}

void		init_t_open_q(t_open_q *o, const char *str)
{
	o->new_line = ft_strdup_and_check("");
	o->save = 0;
	o->append_this = NULL;
	o->str = ft_strdup_and_check(str);
}

void		free_o(t_open_q *o)
{
	free(o->str);
	o->str = NULL;
	o->new_line = NULL;
}

void			open_quotes(t_token *token)
{
	char 		*tmp;
	t_open_q	*o;
	o = malloc(sizeof(t_open_q));
	ft_alloc_check(o);
	static char	tab_[] = {DOLLAR, DOUBLE_QUOTE, BACKSLASH, GRAVE_ACCENT, '\0'};
	o->tab = tab_;
	tmp = NULL;
	while (token)
	{
		init_globs();
		set_token_flag(token, token->content);
		if (token->is_diff)
		{
			token = token->next;
			continue ;
		}
		init_t_open_q(o, token->content);
		tmp = token->content;
		token->content = open_quotes_str(o);
		free(tmp);
		free_o(o);
		token = token->next;
	}
	free(o);
}
