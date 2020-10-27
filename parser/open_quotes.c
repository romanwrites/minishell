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

typedef struct	s_open_q {
	int			i;
	int 		save;
	char		*new_line;
	char		*append_this;
}				t_open_q;

_Bool		is_env_val_after_dollar(char c)
{
	return (ft_isdigit(c) || ft_isalpha(c) || c == DOLLAR);
}

void		handle_dollar_out_of_quotes(char *str, int i, int save, char **new_line)
{
	int		j;
	char 	*append_this;
	char	*value_to_check;
	char 	*env_value;

	j = 0;
	if (str[i + 1] == '$')
	{
		j = get_dollars_end(str + i);
		if (i > save + 2 && is_backslash_active())
		{
			append_this = ft_substr(str, save, i - save - 1);
			append_line(new_line, &append_this);
		}
		else if (i > save + 2 && !is_backslash_active())
		{
			append_this = ft_substr(str, save, i - save);
			append_line(new_line, &append_this);
		}
		append_this = ft_substr(str, i, j);
		append_line(new_line, &append_this);
		i += j;
		save = i + 2;
		return ;
	}
	else if (ft_isdigit(str[i + 1]))
	{
		i += 2;
		save += 2;
		return ;
	}
	j = get_env_from_str(str + i);
	if (is_backslash_active())
	{
		if (i > save + 2)
		{
			append_this = ft_substr(str, save, i - save - 1);
			append_line(new_line, &append_this);
		}
		append_this = ft_substr(str, i, j);
	}
	else
	{
		if (i >= save + 1)
		{
			append_this = ft_substr(str, save, i - save);
			append_line(new_line, &append_this);
		}
		if (j == 2)
			value_to_check = ft_strdup("");
		else
			value_to_check = ft_substr(str, i + 1, j - 1);
		ft_alloc_check(value_to_check);
		env_value = get_envar(value_to_check);
		if (!env_value)
			append_this = ft_strdup("");
		else
		{
			append_this = ft_strdup(env_value);
		}
		if (env_value)
		{
			free(env_value);
			env_value = NULL;
		}
		free(value_to_check);
		value_to_check = NULL;
	}
	append_line(new_line, &append_this);
//	i += j - 1;
//	save = i + 1;
//	i++;
//	continue ;
}



char		*open_quotes_str(const char *str_src)
{
	t_open_q	*o;
	o = malloc(sizeof(t_open_q));
//	char 	*new_line;
	size_t 	i;
	size_t 	j;
	size_t 	save;
	char 	*append_this;
	char 	*str;
	static char	tab[] = {DOLLAR, DOUBLE_QUOTE, BACKSLASH, GRAVE_ACCENT, '\0'};

	char	*value_to_check;
	char 	*env_value;

	i = 0;
	save = 0;
	j = 0;
	append_this = NULL;
	init_globs();
	o->new_line = ft_strdup_and_check("");
	str = ft_strdup_and_check(str_src);
	env_value = NULL;
	while (str[i])
	{
		set_states(str[i]);
		if (is_backslash_active() && !is_open_quote())
		{
			i++;
			append_this = ft_strdup(" ");
			ft_alloc_check(append_this);
			append_this[0] = str[i];
			append_line(&o->new_line, &append_this);
			save = i + 1;
			set_backslash_state_new(str[i]);
		}
		else if (str[i] == DOLLAR && is_env_val_after_dollar(str[i + 1]))
		{
			handle_dollar_out_of_quotes();
		}
		else if (is_open_quote())
		{
			append_this = ft_substr(str, save, i - save);
			ft_alloc_check(append_this);
			append_line(&o->new_line, &append_this);
			save = i;
			while (is_open_quote() && str[++i])
			{
				set_states(str[i]);
				if (str[i] == BACKSLASH && g_dquote && ft_strchr(tab, str[i + 1]))
				{
					i++;
					append_this = ft_strdup(" ");
					ft_alloc_check(append_this);
					append_this[0] = str[i];
					append_line(&new_line, &append_this);
					save = i;
					set_states(str[i]);
				}
				else if (str[i] == DOLLAR && g_dquote && is_env_val_after_dollar(str[i + 1]))
				{
					if (str[i + 1] == '$')
					{
						j = get_dollars_end(str + i);
						if (i > save + 2 && is_backslash_active())
						{
							append_this = ft_substr(str, save, i - save - 1);
							append_line(&new_line, &append_this);
						}
						else if (i > save + 2 && !is_backslash_active())
						{
							append_this = ft_substr(str, save, i - save);
							append_line(&new_line, &append_this);
						}
						append_this = ft_substr(str, i, j);
						append_line(&new_line, &append_this);
						i += j;
						save = i + 2;
						continue ;
					}
					else if (ft_isdigit(str[i + 1]))
					{
						i += 2;
						save += 2;
						continue ;
					}
					j = get_env_from_str(str + i);
					if (is_backslash_active())
					{
						if (i > save + 2)
						{
							append_this = ft_substr(str, save, i - save - 1);
							append_line(&new_line, &append_this);
						}
						append_this = ft_substr(str, i, j);
					}
					else
					{
						if (i > save + 1)
						{
							append_this = ft_substr(str, save, i - save);
							append_line(&new_line, &append_this);
						}
						if (j == 2)
							value_to_check = ft_strdup("");
						else
							value_to_check = ft_substr(str, i + 1, j - 1);
						ft_alloc_check(value_to_check);
						env_value = get_envar(value_to_check);
						if (!env_value)
							append_this = ft_strdup("");
						else
						{
							append_this = ft_strdup(env_value);
						}
                        if (env_value)
                        {
                            free(env_value);
                            env_value = NULL;
                        }
                        free(value_to_check);
                        value_to_check = NULL;
                    }
					append_line(&new_line, &append_this);
					i += j - 1;
					save = i + 1;
					continue ;
				}
				else if (is_open_quote())
				{
					append_this = ft_substr(str, i, 1);
					ft_alloc_check(append_this);
					append_line(&new_line, &append_this);
					save = i;
				}
			}
			save = i + 1;
		}
		else if (i == 0 && str[i] == '~' && !str[i + 1])
		{
			env_value = get_envar("~");
			if (!env_value)
				append_this = ft_strdup("");
			else
			{
				append_this = ft_strdup(env_value);
			}
			append_line(&new_line, &append_this);
			save = i + 1;
			free(env_value);
			env_value = NULL;
			return (new_line);
		}
		i++;
	}
	if (i - save > 1 || \
		(i - save >= 1 && (str[i - 1] == DOUBLE_QUOTE || str[i - 1] == SINGLE_QUOTE)) || \
		(str[0] && !str[1]) || \
		(i - save == 1 && (str[save] != DOUBLE_QUOTE || str[save] != SINGLE_QUOTE)))
	{
		append_this = ft_substr(str, save, i - save);
		ft_alloc_check(append_this);
		append_line(&new_line, &append_this);
	}
	free(str);
	return (new_line);
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

void		open_quotes(t_token *token)
{
	char 	*tmp;

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
		tmp = token->content;
		token->content = open_quotes_str(tmp);
		free(tmp);
		tmp = NULL;
		token = token->next;
	}
}
