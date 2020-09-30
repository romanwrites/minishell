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

void		split_by_pipes(t_mshell *sv, char *str)
{

}

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
	char	*input_str = ft_strtrim(tmp, " \t");
	ft_alloc_check(input_str);
	free(tmp);
	tmp = NULL;
	printf("\ncase: %d, str: %s\nafter split by semicolons:\n", case_num, input_str);

	// STEP 1.0: split by semicolons
	semicolons2d = split_by_char(sv, ';', input_str);
	ft_trim_2d(&semicolons2d);

	print_2d_array(semicolons2d);

	int lines_count = count_2d_lines(semicolons2d);

	t_dlst	*dlst;
	void	*tmp_ptr;
	int j = 0;
//	dlst = (t_dlst *)malloc(sizeof(t_dlst) * lines_count + 1);
//while
	dlst = ft_dlstnew(NULL, NULL);
	ft_alloc_check(dlst);
	while (semicolons2d[j])
	{
		tmp_ptr = (void *)split_by_char(sv, '|', semicolons2d[j]);
		ft_alloc_check(tmp_ptr);
		dlst->content = (void *)ft_dlstnew(tmp_ptr, NULL);
		print_2d_array((char **)dlst->content);
		j++;
	}
//	char	**pipes1 = split_by_char(sv, '|', semicolons2d[j]);
//	print_2d_array(pipes1);


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