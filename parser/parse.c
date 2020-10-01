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

void        check_common(char *str)
{
     if (str)
     {
         if (str[0] == ';' || str[1] == '|' || str[ft_strlen(str)] == '|' || str[ft_strlen(str)] == ';')
         {
             exit_error_message("Bad syntax. check_common()");
         }
     }
}

void		parse_start(t_mshell *sv)
{
	char	*tmp;
	char	**quotes2d;
	char	**semicolons2d;
	static int case_num;
	case_num++;

//	split_sh(sv);  Make one function to split elegantly

	// STEP 0: trim
	char	*input_str = ft_strtrim(sv->content, " \t");
	ft_alloc_check(input_str);
	printf("\ncase: %d, str: [%s]\nafter split by semicolons:\n", case_num, input_str);
    check_common(input_str);
	// STEP 1.0: split by semicolons
	semicolons2d = split_by_char(sv, ';', input_str);
	ft_trim_2d(&semicolons2d);

	print_2d_array(semicolons2d);
    printf("\nDONE\n\nnext split by pipes:\n\n");

	int lines_count = count_2d_lines(semicolons2d);

	t_dlist	*dlst;
    t_dlist	*dlst_head;
	void	*tmp_ptr2d;
	int j = 0;

	dlst = ft_dlstnew(NULL, NULL);
	ft_alloc_check(dlst);

    dlst_head = dlst;
	while (semicolons2d[j])
	{
		tmp_ptr2d = (void *)split_by_char(sv, '|', semicolons2d[j]);
		ft_alloc_check(tmp_ptr2d);
		dlst->content = (void *)ft_dlstnew(tmp_ptr2d, NULL);
        tmp_ptr2d = NULL;
        char **ptr = (char **)((t_dlist *)dlst->content)->content;
        ft_trim_2d(&ptr); // do need to pass as address?

		print_2d_array((char **)((t_dlist *)dlst->content)->content);
		dlst->next = ft_dlstnew(NULL, NULL);
		dlst = dlst->next;
		j++;
	}
	ft_free2d(semicolons2d);
	semicolons2d = NULL;

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