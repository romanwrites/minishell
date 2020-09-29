/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 17:38:07 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/29 22:44:28 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		parse_start(t_mshell *sv)
{
	char	*tmp;
	char	**quotes2d;

	static int case_num;
	case_num++;

	tmp = sv->content;

//	split_sh(sv);  Make one function to split elegantly

	// STEP 0: trim
	sv->content = ft_strtrim(tmp, " \t");
	ft_alloc_check(sv->content);
	free(tmp);
	tmp = NULL;
	printf("case: %d, str: %s\nafter split by quotes:\n", case_num, sv->content);

	// STEP 1: split by quotes
	quotes2d = split_by_quotes(sv);
	print_2d_array(quotes2d);
	ft_putchar('\n');

	// STEP 2: trim and split by semicolons
	ft_trim_2d(&quotes2d);
	print_2d_array(quotes2d);
	ft_putchar('\n');
	ft_free2d(quotes2d);
}