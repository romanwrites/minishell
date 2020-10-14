/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 17:38:07 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/14 16:19:34 by lhelper          ###   ########.fr       */
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
	char    tab[] = {47, 92, 36, 34, 39, '\0'};

	i = 1;
	while (str[i])
	{
		if (ft_strchr(tab, str[i]) != NULL)
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

void        check_doubles(t_mshell *sv, const char *str, char c)
{
    int     i;

    i = 0;
    while (str[i])
    {
        set_backslash_state(sv->state, str[i]);
        if (i > 0 && !is_backslash_pressed(sv->state) && str[i] == c && str[i + 1] == c)
            exit_error_message("command not found. check_doubles()");
        i++;
    }
}

size_t		get_dollars_end(const char *str)
{
    size_t	i;

    i = 0;
    while (str[i] == '$')
	{
    	i++;
	}
    return (i);
}

void		handle_env(t_mshell *sv, char **str)
{
	char	*ptr;
	char	*new_str;
	size_t		i;
    size_t		j;
    size_t		save;
	char	*env_value;
	char    *value_to_check;
	char    *append_this;

	i = 0;
	j = 0;
	save = 0;
    env_value = NULL;
	new_str = ft_strdup("");
	value_to_check = NULL;
	ft_alloc_check(new_str);
    state_bzero(sv->state);
	if (str)
	{
		ptr = *str;
		while (ptr[i])
		{
            set_backslash_state(sv->state, ptr[i]);
			if (ptr[i] == '$')
			{
			    if (ptr[i + 1] == '$')
                {
                    j = get_dollars_end(ptr + i);
					if (i > save + 2 && is_backslash_pressed(sv->state))
					{
						append_this = ft_substr(ptr, save, i - save - 1);
						append_line(&new_str, &append_this);
					}
					else if (i > save + 2 && !is_backslash_pressed(sv->state))
					{
						append_this = ft_substr(ptr, save, i - save);
						append_line(&new_str, &append_this);
					}
					append_this = ft_substr(ptr, i, j);
					append_line(&new_str, &append_this);
					i += j;
					save = i + 2;
					continue ;
                }
                j = get_env_from_str(ptr + i);
                if (is_backslash_pressed(sv->state))
                {
                    if (i > save + 2)
                    {
                        append_this = ft_substr(ptr, save, i - save - 1);
                        append_line(&new_str, &append_this);
                    }
                    append_this = ft_substr(ptr, i, j);
                }
                else
                {
                    if (i > save + 1)
                    {
                        append_this = ft_substr(ptr, save, i - save);
                        append_line(&new_str, &append_this);
                    }
                    if (j == 2)
                        value_to_check = ft_strdup("");
                    else
                        value_to_check = ft_substr(ptr, i + 1, j - 1);
                    ft_alloc_check(value_to_check);
                    env_value = get_envar(value_to_check);
                    if (!env_value)
                        append_this = ft_strdup("");
                    else
                    {
                        append_this = ft_strdup(env_value);
                    }
                }
                append_line(&new_str, &append_this);
                i += j - 1;
                save = i + 1;
            }
			i++;
		}
        if (i > save + 1)
        {
            append_this = ft_substr(ptr, save, i - save);
            append_line(&new_str, &append_this);
        }
		free(*(str));
		*(str) = new_str;
	}
}

int     count_chr(const char *str, char c, _Bool pos)
{
    size_t i;

    if (!pos)
    {
        i = 0;
        while (str[i] && str[i] == c)
            i++;

    }
    else
    {
        i = ft_strlen(str) - 1;
        while (str[i] && str[i] == c)
            i--;
        i = ft_strlen(str) - 1 - i;
    }
    return (i);
}

void		parse_env(t_mshell *sv)
{
	t_dlist *dlst;
	char	**ptr;
	int 	i;
	char    *tmp;

	i = 0;
	dlst = sv->dlst_head;
	while (dlst)
	{
		ptr = (char **)dlst->content;
		while (ptr && ptr[i])
		{
		    if (ptr[i][0] == 39)
		    {
                tmp = ptr[i];
                if (count_chr(ptr[i], 39, 0) != count_chr(ptr[i], 39, 1)) {
                    exit_error_message("syntax error, singly quotes are not closed. parse_env()");
                }
                if (count_chr(ptr[i], 39, 0) % 2 == 1) {
                    ptr[i] = ft_strtrim(tmp, "'");
                    i++;
                    continue;
                } else {
                    ptr[i] = ft_strtrim(tmp, "'");
                }
                free(tmp);
                tmp = NULL;
            }
		    else if (ptr[i][0] == 34)
            {
                tmp = ptr[i];
                if (count_chr(ptr[i], 34, 0) != count_chr(ptr[i], 34, 1))
                {
                    exit_error_message("syntax error, singly quotes are not closed. parse_env()");
                }
                ptr[i] = ft_strtrim(tmp, "\"");
                free(tmp);
                tmp = NULL;
            }
            if (ft_strchr(ptr[i], (int)'$'))
				handle_env(sv, &ptr[i]);
			i++;
		}
		dlst = dlst->next;
	}
}

char		*get_new_str_qopen(t_mshell *sv, char **new)
{
	int 	i;
	char 	*str;
	char 	*tmp;

	i = 0;
	str = *(new);
	while (str[i])
	{
		set_backslash_state(sv->state, str[i]);
		set_quotes_state(sv, sv->state, i, str);

		i++;
	}
}

char		*open_quotes_str(t_parse *state, char *str)
{
	char 	*new;
	size_t 	i;
	size_t 	len;

	i = 0;
	len = ft_strlen(str);
	if ((str[i] == 34 && str[len] == 34) || (str[i] == 39 && str[len] == 39))
	{
		i = 1;
		len -= 1;
		new = ft_substr(str, i, len);
		ft_alloc_check(new);
	}
	else
	{
		new = ft_strdup(str);
		ft_alloc_check(new);
	}
	new = get_new_str_qopen(sv, &new);
	return (new);
}

void		open_quotes_2d(t_mshell *sv, char ***ptr)
{
	char	**ptr_2d;
	char 	*tmp;
	int 	i;

	i = 0;
	ptr_2d = *(ptr);
	while (ptr_2d[i])
	{
		state_bzero(sv->state);
		tmp = ptr_2d[i];
		ptr_2d[i] = open_quotes_str(sv->state, tmp);
		free(tmp);
		tmp = NULL;
		i++;
	}
}

void		parse_input(t_mshell *sv)
{
	char	**semicolons2d;
	char	*input_str;
	t_dlist	*dlst;
	char	**tmp_ptr2d;
	int		j;

	j = 0;
	input_str = ft_strtrim(sv->content, " \t");
	ft_alloc_check(input_str);
	check_common(input_str);
	semicolons2d = split_by_char(sv, ';', input_str);
	ft_trim_2d(&semicolons2d);
	dlst = ft_dlstnew(NULL, NULL);
	ft_alloc_check(dlst);
    sv->dlst_head = dlst;
	while (semicolons2d[j])
	{
	    if (is_bad_syntax(semicolons2d[j][0]))
	        exit_error_message("bad syntax");
		state_bzero(sv->state);
		tmp_ptr2d = split_command(sv, semicolons2d[j]);
		open_quotes_2d(sv, &tmp_ptr2d);

		dlst->content = (void *)tmp_ptr2d;
		tmp_ptr2d = NULL;
        char **ptr = (char **)dlst->content;
        ft_trim_2d(&ptr);
        if (count_2d_lines(ptr) == 1 && is_bad_syntax(ptr[0][ft_strlen(ptr[0]) - 1]))
            exit_error_message("bad syntax");
		dlst->next = ft_dlstnew(NULL, NULL);
		ft_alloc_check(dlst->next);
		dlst = dlst->next;
		j++;
	}
	ft_free2d(semicolons2d);
	semicolons2d = NULL;
	dlst = NULL;
    state_bzero(sv->state);
	parse_env(sv);
}
