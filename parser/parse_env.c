
#include "minishell.h"

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


int			get_env_from_str(const char *str)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isalpha(str[i]))
			break ;
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
	init_globs();
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
//                if (count_chr(ptr[i], 39, 0) != count_chr(ptr[i], 39, 1)) {
//                    exit_error_message("syntax error, singly quotes are not closed. parse_env()");
//                }
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
//                if (count_chr(ptr[i], 34, 0) != count_chr(ptr[i], 34, 1))
//                {
//                    exit_error_message("syntax error, singly quotes are not closed. parse_env()");
//                }
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