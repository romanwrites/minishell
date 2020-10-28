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
	print_error("syntax error");
	g_exit = 258;
	return (1);
}

_Bool		parse_input(char *str, t_mshell *sv)
{
	char	**semicolons2d;
	char	*input_str;

	init_globs();
	input_str = ft_strtrim(str, " ");
	ft_alloc_check(input_str);
	if (check_syntax_by_indexes(input_str) || check_syntax_errors(input_str))
		ret_syntax_err();
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
	return (0);
}
