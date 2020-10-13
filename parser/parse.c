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

int			get_env_from_str(const char *str)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '/' || str[i] == '$')
			break ;
		i++;
	}
	return (i);
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

void		handle_env(t_mshell *sv, char **str)
{
	char	*ptr;
	char	*new_str;
	size_t		i;
    size_t		j;
	_Bool	is_alloc;
	char	*env_value;
	char	*tmp_env_val;
	char	*tmp_append;
	char    *value_to_check;
	char    *append_this;

	i = 0;
	j = 0;
	is_alloc = 0;
    env_value = NULL;
	new_str = ft_strdup("");
	ft_alloc_check(new_str);
	if (str)
	{
		ptr = *str;
		while (ptr[i])
		{
			if (ptr[i] == '$')
			{
			    if (i > ft_strlen(new_str) + 1)
                {
			        append_this = ft_substr(ptr, ft_strlen(new_str), i - (ft_strlen(new_str) + 1));
                    append_line(&new_str, &append_this);
                }
                j = get_env_from_str(ptr + i);
                if (j == 2)
                    value_to_check = ft_strdup("");
                else
                    value_to_check = ft_substr(ptr, i + 1, j - 1);
                ft_alloc_check(value_to_check);
                env_value = get_envar(sv->envp_mshell, value_to_check);
                if (!env_value)
                    append_this = ft_strdup("");
                else
                    append_this = env_value;
                append_line(&new_str, &append_this);
                i += j - 1;
            }
			i++;
		}
		free(*(str));
		*(str) = new_str;
	}
}

void		parse_env(t_mshell *sv)
{
	t_dlist *dlst;
	char	**ptr;
	int 	i;

	i = 0;
	dlst = sv->dlst_head;
	while (dlst)
	{
		ptr = (char **)dlst->content;
		while (ptr && ptr[i])
		{
			if (ft_strchr(ptr[i], (int)'$'))
				handle_env(sv, &ptr[i]);
			i++;
		}
		print_2d_array(ptr);
		dlst = dlst->next;
	}
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
	parse_env(sv);
}
