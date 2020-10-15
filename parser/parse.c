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
		set_quotes_state(sv->state, i, str);

		i++;
	}
}




size_t		len_without_newlines(const char *ptr)
{
	size_t	i;
	size_t 	j;

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

char		*realloc_without_newlines(char **append_this)
{
	char	*new_str;
	char	*ptr;
	int 	i;
	int 	j;

	i = 0;
	j = 0;
	ptr = *(append_this);
	new_str = malloc(len_without_newlines(ptr));
	ft_alloc_check(new_str);
	while (ptr[i])
	{
		if (ptr[i] != '\n')
		{
			new_str[j] = ptr[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	free(ptr);
	*(append_this) = NULL;
	return (new_str);
}

char		*open_quotes_str(t_parse *state, const char *str_src)
{
	char 	*new_line;
	size_t 	i;
	size_t 	j;
	size_t 	save;
	char 	*append_this;
	char 	*str;
	char	tab[] = {DOLLAR, DOUBLE_QUOTE, BACKSLASH, GRAVE_ACCENT};

	char	*value_to_check;
	char 	*env_value;

	i = 0;
	save = 0;
	j = 0;
	append_this = NULL;
	init_globs();
	new_line = ft_strdup("");
	ft_alloc_check(new_line);
	str = ft_strdup(str_src);
	ft_alloc_check(str);
	while (str[i])
	{
		set_backslash_state_new(str[i]);
		set_quotes_state_new(str[i]);
		if (str[i] == DOLLAR)
		{
			if (str[i + 1] == '$')
			{
				j = get_dollars_end(str + i);
				if (i > save + 2 && is_backslash_active())
				{
					append_this = ft_substr(str, save, i - save - 1);
					append_line(&new_line, &append_this);
				}
				else if (i > save + 2 && !is_backslash_active())
				{
					append_this = ft_substr(str, save, i - save);
					append_line(&new_line, &append_this);
				}
				append_this = ft_substr(str, i, j);
				append_line(&new_line, &append_this);
				i += j;
				save = i + 2;
				continue ;
			}
			j = get_env_from_str(str + i);
			if (is_backslash_active())
			{
				if (i > save + 2)
				{
					append_this = ft_substr(str, save, i - save - 1);
					append_line(&new_line, &append_this);
				}
				append_this = ft_substr(str, i, j);
			}
			else
			{
				if (i > save + 1)
				{
					append_this = ft_substr(str, save, i - save);
					append_line(&new_line, &append_this);
				}
				if (j == 2)
					value_to_check = ft_strdup("");
				else
					value_to_check = ft_substr(str, i + 1, j - 1);
				ft_alloc_check(value_to_check);
				env_value = get_envar(value_to_check);
				if (!env_value)
					append_this = ft_strdup("");
				else
				{
					append_this = ft_strdup(env_value);
				}
			}
			append_line(&new_line, &append_this);
			i += j - 1;
			save = i + 1;
			i++;
			continue ;
		}
		if (is_open_quote())
		{
			append_this = ft_substr(str, save, i - save);
			ft_alloc_check(append_this);
			append_line(&new_line, &append_this);
			j = i;
			while (is_open_quote() && str[++j])
			{
				set_backslash_state_new(str[j]);
				set_quotes_state_new(str[j]);
				if (is_backslash_active() && g_dquote && ft_strchr(tab, str[j + 1]))
				{
					str[j] = '\n';
					j++;
				}
			}
			if (j - i > 1)
			{
				append_this = ft_substr(str, i + 1, j - i - 1);
				ft_alloc_check(append_this);
				if (ft_strchr(append_this, '\n'))
				{
					append_this = realloc_without_newlines(&append_this);
				}
				append_line(&new_line, &append_this);
			}
			save = j + 1;
			i = j;
		}
		i++;
	}
	if (i - save > 1)
	{
		append_this = ft_substr(str, save, i - save);
		ft_alloc_check(append_this);
		append_line(&new_line, &append_this);
	}
	return (new_line);
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
		init_globs();
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
		init_globs();
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
//	init_globs();
//	parse_env(sv);
}
