/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 17:38:07 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/28 20:02:27 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		append_line(char **ptr, char **append_this)
{
	char	*tmp_ptr;
	char	*new_line;
	char	*tmp_append;

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
	size_t	j;

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

_Bool		ret_syntax_err(void)
{
	print_error(SYNTAX_ERROR);
	g_exit = 258;
	return (1);
}

int				count_tokens(t_token *token)
{
	t_token		*ptr;
	int			i;

	i = 0;
	ptr = token;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

char			**token_to_2d_array(t_token *token, int len)
{
	char		**tokens_2d;
	t_token		*ptr;
	int			i;

	i = 0;
	ptr = token;
	tokens_2d = malloc(sizeof(char *) * (len + 1));
	ft_alloc_check(tokens_2d);
	while (ptr)
	{
		tokens_2d[i++] = ft_strdup_and_check(ptr->content);
		ptr = ptr->next;
	}
	tokens_2d[i] = NULL;
	return (tokens_2d);
}

_Bool			check_syntax_token(t_token *token)
{
	char		**tokens_2d;

	tokens_2d = token_to_2d_array(token, count_tokens(token));
	if (check_syntax_2d(tokens_2d))
	{
		ft_free2d(tokens_2d);
		return (1);
	}
	ft_free2d(tokens_2d);
	return (0);
}


_Bool		check_tokens_syntax(t_mshell *sv)
{
	while (sv->sh)
	{
		while (sv->sh->tdlst_pipe)
		{
			if (check_syntax_token(sv->sh->tdlst_pipe->token))
				return (1);
			sv->sh->tdlst_pipe->token = sv->sh->tdlst_pipe->token_head;
			sv->sh->tdlst_pipe = sv->sh->tdlst_pipe->next;
		}
		sv->sh->tdlst_pipe = sv->sh->tdlst_pipe_head;
		sv->sh = sv->sh->next;
	}
	sv->sh = sv->sh_head;
	return (0);
}

_Bool		parse_input(char *str, t_mshell *sv)
{
	char	**semicolons2d;
	char	*input_str;

	init_globs();
	input_str = ft_strtrim(str, " ");
	ft_alloc_check(input_str);
	if (check_syntax_by_indexes(input_str) || check_syntax_errors(input_str))
		return (ret_syntax_err());
	semicolons2d = split_by_char(SEMICOLON, input_str, sv);
	ft_alloc_check(semicolons2d);
	free(input_str);
	input_str = NULL;
	init_globs();
	if (!(sv->sh = get_sh_list(semicolons2d, 0, sv)))
		return (1);
	ft_free2d(semicolons2d);
	semicolons2d = NULL;
	if (!sv->sh)
		return (1);
	set_heads(sv);
	if (check_tokens_syntax(sv))
		return (1);
	return (0);
}
