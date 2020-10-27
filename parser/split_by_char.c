/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 00:49:14 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/30 00:49:17 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_new_lines_over_char(char c, char *str, t_mshell *sv)
{
	int		j = 0;

	while (str[j])
	{
		set_backslash_state(sv->state, str[j]);
		set_quotes_state(sv->state, j, str);
		if (str[j] == c && !is_any_quote_open(sv->state) && \
							!is_backslash_pressed(sv->state))
		{
//			if (str[j + 1] == c)
//			{
//				exit_error_message("bash: syntax error near unexpected token `;;'"); // set 258
//				return ; //debug
//			}
			str[j] = '\n';
		}
//		if (j > 0 && str[j] == c && str[j - 1] == '\n')
//		{
//			exit_error_message("bash: syntax error near unexpected token `;;'"); //edit error message with prompt and set 258
//			return ; //debug
//		}
//		if (j == 0 && str[j] == c)
//		{
//			exit_error_message("bash: syntax error near unexpected token `;'"); //258
//			return ; //debug
//		}
		j++;
	}
}

char		**split_by_char(char c, char *str, t_mshell *sv)
{
	char	**semicolon2d;
	char 	**new_ptr;

	set_new_lines_over_char(c, str, sv);
	semicolon2d = ft_split(str, '\n');
	reset_newlines(str);
	ft_alloc_check(semicolon2d);
	new_ptr = ft_trim_2d_cpy(semicolon2d);
	return (new_ptr);
}
