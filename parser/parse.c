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

typedef struct	s_dllst {
	void		*previous;
	void		*next;
	void		*content;
}				t_dllst;

void		parse_start(t_mshell *sv)
{
	char	*tmp;
	char	**quotes2d;
	char	**semicolons2d;

	static int case_num;
	case_num++;

	tmp = sv->content;

//	split_sh(sv);  Make one function to split elegantly

	printf("sizeof(void *): %zu\n", sizeof(void *));
	printf("sizeof(char *): %zu\n", sizeof(char *));
	printf("sizeof(char **): %zu\n", sizeof(char **));
	printf("sizeof(char ***): %zu\n", sizeof(char ***));

	// STEP 0: trim
	sv->content = ft_strtrim(tmp, " \t");
	ft_alloc_check(sv->content);
	free(tmp);
	tmp = NULL;
	printf("\ncase: %d, str: %s\nafter split by semicolons:\n", case_num, sv->content);

	// STEP 1.0: split by semicolons
	semicolons2d = split_by_semicolons(sv);
	print_2d_array(semicolons2d);

//	// STEP 1: split by quotes
//	printf("case: %d, str: %s\nafter split by quotes:\n", case_num, sv->content);
//	quotes2d = split_by_quotes(sv);
//	print_2d_array(quotes2d);
//	ft_putchar('\n');
//
//	// STEP 2: trim
//	ft_trim_2d(&quotes2d);
//	print_2d_array(quotes2d);
//	ft_putchar('\n');
//
//	// STEP 3: split by semicolons
//
//	ft_free2d(quotes2d);
}