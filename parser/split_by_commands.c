/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 05:53:19 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/07 05:53:29 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		set_nl_cpy(char **str, int i)
{
	char		*tmp;
	char		*new;

	tmp = *str;
	new = malloc(ft_strlen(tmp) + 2);
	ft_alloc_check(new);
	ft_memcpy(new, tmp, i);
	new[i] = '\n';
	ft_memcpy(new + i + 1, tmp + i, ft_strlen(tmp) - i + 1);
	free(tmp);
	*str = new;
	return (1);
}

static int		process_open_q_cmd(char *str, int j)
{
	while (is_open_quote() && str[j])
	{
		set_states(str[j]);
		j++;
	}
	return (j);
}

static char		*process_str(const char *str_input)
{
	int			i;
	char		*str;

	str = ft_strdup_and_check(str_input);
	i = 0;
	while (str[i])
	{
		set_states(str[i]);
		if (is_open_quote())
			i = process_open_q_cmd(str, ++i) - 1;
		else if (ft_isspace(str[i]) && !is_backslash_active())
			str[i] = '\n';
		else if (i > 0 && is_pipe_or_single_redir(str, i))
			i += set_nl_cpy(&str, i);
		else if (i > 0 && is_double_redir(str, i))
			i += set_nl_cpy(&str, i) + 1;
		else if (i > 1 && is_after_redir(str, i))
			i += set_nl_cpy(&str, i);
		else if (i > 0 && is_after_redir_or_pipe(str, i))
			i += set_nl_cpy(&str, i);
		else if (i > 0 && is_after_redir_semi_check(str, i))
			set_nl_cpy(&str, i);
		i++;
	}
	return (str);
}

char			**split_command(const char *str_input)
{
	char		**split_by_spaces;
	char		*str;

	init_globs();
	str = process_str(str_input);
	if (is_open_quote())
		exit_error_message("Quotes are open: split_command()");
	split_by_spaces = ft_split(str, '\n');
	ft_alloc_check(split_by_spaces);
	reset_newlines(str);
	free(str);
	str = NULL;
	return (split_by_spaces);
}
