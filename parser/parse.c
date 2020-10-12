/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 17:38:07 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/10 18:47:56 by lhelper          ###   ########.fr       */
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

char		*analise_command(char **arr_2d)
{
	int 	i;
	char 	*str;

	i = 0;
	while (arr_2d[i])
	{
		i++;
	}
	return NULL;
}

void		create_commands_list(t_mshell *sv)
{
	t_dlist *dlst;
	t_dlist	*commands;
	char *str;

	dlst = sv->dlst_head;
	commands = ft_dlstnew(NULL, NULL);
	ft_alloc_check(commands);
	while (dlst)
	{
		str = analise_command((char **)((t_dlist *)dlst->content)->content);
		dlst = dlst->next;
	}
}

_Bool   is_bad_syntax(char c)
{
    int     i;
    char    tab[] = ";|><";

    i = 0;
    while(tab[i])
    {
        if (tab[i] == c)
            return (1);
        i++;
    }
    return (0);
}

void		parse_input(t_mshell *sv)
{
	char	*tmp;
	char	**semicolons2d;
	static int case_num;
	case_num++;
//	split_sh(sv);  Make one function to split elegantly

	char	*input_str = ft_strtrim(sv->content, " \t");
	ft_alloc_check(input_str);
//	printf("\ncase: %d, str: [%s]\nafter split by semicolons:\n", case_num, input_str);
    check_common(input_str);
	semicolons2d = split_by_char(sv, ';', input_str);
	ft_trim_2d(&semicolons2d);

//	print_2d_array(semicolons2d);
//    printf("\nDONE\n\nnext split by pipes:\n\n");

	t_dlist	*dlst;

	char	**tmp_ptr2d;
	int j = 0;
//    get_envar(sv->envp_mshell, "PATH"
	dlst = ft_dlstnew(NULL, NULL);
	ft_alloc_check(dlst);
    sv->dlst_head = dlst;
	while (semicolons2d[j])
	{
	    if (is_bad_syntax(semicolons2d[j][0]))
	        exit_error_message("bad syntax");
		state_bzero(sv->state);
		tmp_ptr2d = split_command(sv, semicolons2d[j]);
		dlst->content = (void *)tmp_ptr2d;
		tmp_ptr2d = NULL;
        char **ptr = (char **)dlst->content;
        ft_trim_2d(&ptr);
        if (count_2d_lines(ptr) == 1 && is_bad_syntax(ptr[0][ft_strlen(ptr[0]) - 1]))
            exit_error_message("bad syntax");
//		print_2d_array((char **)dlst->content); //debug print
		dlst->next = ft_dlstnew(NULL, NULL);
		ft_alloc_check(dlst->next);
		dlst = dlst->next;
		j++;
	}
	ft_free2d(semicolons2d);
	semicolons2d = NULL;
	dlst = NULL;
}
