/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 17:38:07 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/17 15:02:12 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool			check_syntax_by_indexes(const char *str)
{
	size_t 	len;

	len = ft_strlen(str);
	if (str[0] == PIPE || str[0] == SEMICOLON)
		return (1);
	else if (str[len] == REDIR_LEFT && len > 1 && str[len - 1] != BACKSLASH)
		return (1);
	else if (str[len] == REDIR_RIGHT && len > 1 && str[len - 1] != BACKSLASH)
		return (1);
	return (0);
}

_Bool			check_sequence(char c1, char c2)
{
	if (c1 == SEMICOLON && (c2 == SEMICOLON || c2 == PIPE))
		return (1);
	else if (c1 == PIPE && (c2 == PIPE || c2 == SEMICOLON))
		return (1);
	else if (c1 == REDIR_LEFT && c2 == PIPE)
		return (1);

	return (0);
}

_Bool			check_syntax_errors(const char *str)
{
	int 	i;
	int 	j;

	i = 0;
	j = 0;
	if (str)
	{
		if (check_syntax_by_indexes(str))
			return (1);
		while (str[i])
		{
			set_backslash_state_new(str[i]);
			set_quotes_state_new(str[i]);
			if (is_open_quote())
			{
				while (str[i++] && is_open_quote())
				{
					set_backslash_state_new(str[i]);
					set_quotes_state_new(str[i]);
				}
				continue ;
			}
			if (ft_isspace(str[i]))
			{
				j = i - 1;
				while (ft_isspace(str[i]))
				{
					set_backslash_state_new(str[i]);
					set_quotes_state_new(str[i]);
					i++;
				}
				if (str[i] && check_sequence(str[j], str[i]))
					return (1);
			}
			else if (!is_open_quote() && i > 0 && !is_backslash_active() \
						&& check_sequence(str[i - 1], str[i]))
			{
				return (1);
			}
			i++;
		}
	}
	return (0);
}

void        append_line(char **ptr, char **append_this)
{
    char    *tmp_ptr;
    char    *new_line;
    char    *tmp_append;

    tmp_ptr = *(ptr);
    new_line = ft_strjoin(tmp_ptr, *(append_this));
    ft_alloc_check(new_line);
    free(tmp_ptr);
    tmp_ptr = NULL;
    *(ptr) = new_line;
    tmp_append = *(append_this);
    free(tmp_append);
    *(append_this) = NULL;
    new_line = NULL;
}

size_t		len_without_newlines(const char *ptr)
{
	size_t	i;
	size_t 	j;

	i = 0;
	j = 0;
	while (ptr[i])
	{
		if (ptr[i] != '\n')
			j++;
		i++;
	}
	return (j);
}

char		*realloc_without_newlines(char **append_this)
{
	char	*new_str;
	char	*ptr;
	int 	i;
	int 	j;

	i = 0;
	j = 0;
	ptr = *(append_this);
	new_str = malloc(len_without_newlines(ptr));
	ft_alloc_check(new_str);
	while (ptr[i])
	{
		if (ptr[i] != '\n')
		{
			new_str[j] = ptr[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	free(ptr);
	*(append_this) = NULL;
	return (new_str);
}

_Bool		is_env_val_after_dollar(char c)
{
	return (ft_isdigit(c) || ft_isalpha(c) || c == DOLLAR);
}

char		*open_quotes_str(const char *str_src)
{
	char 	*new_line;
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
	new_line = ft_strdup("");
	ft_alloc_check(new_line);
	str = ft_strdup(str_src);
	ft_alloc_check(str);
	env_value = NULL;
	while (str[i])
	{
		set_backslash_state_new(str[i]);
		set_quotes_state_new(str[i]);
		if (is_backslash_active() && !is_open_quote())
		{
			i++;
			append_this = ft_strdup(" ");
			ft_alloc_check(append_this);
			append_this[0] = str[i];
			append_line(&new_line, &append_this);
			save = i + 1;
			set_backslash_state_new(str[i]);
//			set_quotes_state_new(str[i]);
		}
		else if (str[i] == DOLLAR && is_env_val_after_dollar(str[i + 1]))
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
			}
			append_line(&new_line, &append_this);
			i += j - 1;
			save = i + 1;
			i++;
			continue ;
		}
		else if (is_open_quote())
		{
			append_this = ft_substr(str, save, i - save);
			ft_alloc_check(append_this);
			append_line(&new_line, &append_this);
			save = i;
			while (is_open_quote() && str[++i])
			{
				set_backslash_state_new(str[i]);
				set_quotes_state_new(str[i]);
				if (str[i] == BACKSLASH && g_dquote && ft_strchr(tab, str[i + 1]))
				{
					i++;
					append_this = ft_strdup(" ");
					ft_alloc_check(append_this);
					append_this[0] = str[i];
					append_line(&new_line, &append_this);
					save = i;
					set_backslash_state_new(str[i]);
					set_quotes_state_new(str[i]);
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
					}
					append_line(&new_line, &append_this);
					i += j - 1;
					save = i + 1;
//					i++;
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
	return (new_line);
}

void		open_quotes(t_token **tok)
{
	t_token 	*token;
	char 	*tmp;

	token = *(tok);
	while (token)
	{
		init_globs();
		tmp = token->content;
		token->content = open_quotes_str(tmp);
		free(tmp);
		tmp = NULL;
		token = token->next;
	}
}

t_token		*alloc_token_list(char **ptr)
{
	t_token	*token;
	t_token	*head;
	int 	i;

	i = 0;
	token = token_new(ptr[i], NULL);
	ft_alloc_check(token);
	head = token;
	while (ptr[++i])
	{
		token->next = token_new(ptr[i], &token);
		ft_alloc_check(token->next);
		token = token->next;
	}
	return (head);
}

t_dlist_pipe	*alloc_pipe_list(char **ptr)
{
	int 		i;
	char 		**tmp_cmd;
	t_token		*token;
	t_dlist_pipe	*pipe;
	t_dlist_pipe	*head;

	i = 0;
	tmp_cmd = NULL;
	pipe = pipe_new(NULL, NULL);
	ft_alloc_check(pipe);
	head = pipe;
	while (ptr[i])
	{
		tmp_cmd = split_command(ptr[i]);
		ft_alloc_check(tmp_cmd);
		ft_trim_2d(&tmp_cmd);
		token = alloc_token_list(tmp_cmd);
		ft_alloc_check(token);
		tmp_cmd = NULL;
		pipe->token = token;
		pipe->next = pipe_new(NULL, &pipe);
		ft_alloc_check(pipe->next);
		pipe = pipe->next;
		i++;
	}
	return (head);
}

t_dlist_sh			*get_sh_list(char **semicolons2d)
{
	t_dlist_pipe	*dlst_pipe;
	t_dlist_sh		*sh;
	t_dlist_sh		*sh_head;
	char			**tmp_semi;
	int 			i;

	i = 0;
	sh = sh_new(NULL, NULL);
	ft_alloc_check(sh);
	sh_head = sh;
	tmp_semi = NULL;
	while (semicolons2d[i])
	{
		tmp_semi = split_by_char(PIPE, semicolons2d[i]);
		ft_alloc_check(tmp_semi);
		ft_trim_2d(&tmp_semi);
		dlst_pipe = alloc_pipe_list(tmp_semi);
		ft_free2d(tmp_semi);
		tmp_semi = NULL;
		sh->tdlst_pipe = dlst_pipe;
		sh->next = sh_new(NULL, NULL);
		ft_alloc_check(sh->next);
		sh = sh->next;
		i++;
	}
	return (sh_head);
}

_Bool		parse_input(char *str)
{
	char **semicolons2d;
	char *input_str;

	init_globs();
	input_str = ft_strtrim(str, " \t");
	ft_alloc_check(input_str);
	if (check_syntax_errors(input_str))
	{
		print_error("syntax error");
		return (1);
	}
	semicolons2d = split_by_char(SEMICOLON, input_str);
	ft_alloc_check(semicolons2d);
	free(input_str);
	ft_trim_2d(&semicolons2d);
	init_globs();
	g_sv->sh = get_sh_list(semicolons2d);
	g_sv->sh_head = g_sv->sh;
	ft_free2d(semicolons2d);
	semicolons2d = NULL;
	return (0);
}
