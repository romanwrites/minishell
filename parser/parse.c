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
		if (ptr[i + 1])
		{
			pipe->next = pipe_new(NULL, &pipe);
			ft_alloc_check(pipe->next);
			pipe = pipe->next;
		}
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
		if (semicolons2d[i + 1])
		{
			sh->next = sh_new(NULL, NULL);
			ft_alloc_check(sh->next);
			sh = sh->next;
		}
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
