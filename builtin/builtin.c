/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:33:29 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/14 23:42:20 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "../includes/minishell.h"

void	ft_echo(char *str, int flag_n) //"" '' \n \t \0!!!!!!!!!!!!!!!!!!!!!!!!!
{
	write(1, str, ft_strlen(str));
	if (!flag_n)
		write(1, "\n", 1);
}

void	ft_exit(int exit_code)
{
	//ft_lstclear()
	exit(exit_code);
}

void	ft_pwd()
{
	char path[PATH_MAX];

	getcwd(path, PATH_MAX);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
}

void	ft_cd(char *str)
{
	DIR *dir;

	dir = NULL;
	dir = opendir(str);
	if (!dir)
	{
		write(1, "cd: ", ft_strlen("cd: "));
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, ": ", ft_strlen(": "));
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		return ;
	}
	closedir(dir);
	chdir(str);
}

void free_nothing(void *to_free)
{
	return;
}

void	free_content(void *to_free) //should be pointed be del() in ft_lstclear()
{
	t_envar *content;

	content = to_free;
	free(content->key);
	free(content->value);
}

void	ft_env()
{
	t_list *env;
	t_list *exp;

	env = g_env;
	while(env)
	{
		if (((t_envar *)env->content)->value)
		{
			write(1, ((t_envar *)env->content)->key, ft_strlen(((t_envar *)env->content)->key));
			write(1, "=", 1);
			write(1, ((t_envar *)env->content)->value, ft_strlen(((t_envar *)env->content)->value));
			write(1, "\n", 1);
		}
		env = env->next;
	}
}

t_list	*ft_merge_lists(t_list *dst, t_list *src)
{
	t_list *t_dst;
	t_list *t_src;

	if(src == NULL)
		return(dst);
	t_dst = dst;
	t_src = src;
	while (t_src)
	{
		if (!t_dst)
			t_dst = ft_lstnew(t_src->content);
		else
			ft_lstadd_back(&t_dst, ft_lstnew(t_src->content));
		t_src = t_src->next;
	}
	return(t_dst);
}

int		find_key_replace_val(t_list **lst, char *key, char *value)
{
	t_list *tmp;

	tmp = *lst;
	while (tmp)
	{
		if(!ft_strcmp(((t_envar *)tmp->content)->key, key))
		{
			free(((t_envar *)tmp->content)->value);
			((t_envar *)tmp->content)->value = ft_strdup(value);
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}

void	ft_export(char *arg)
{
	t_list	*list;
	t_envar *kv;
	char	**pair;
	char	*value;
	
	list = NULL;
	pair = ft_split(arg, ' ');
	while(pair && *pair)
	{
		kv = malloc(sizeof(t_envar));
		if (!kv)
			return ;
		value = ft_strchr(*pair, '=');
		if (!value)
		{
			kv->value = NULL;//WHEN THERE IS NO '='
			kv->key = ft_strdup(*pair);
			if (!kv->key)
				return ;//what to do if malloc fails
		}
		else if (*(value + 1) == '\0')
		{
			kv->value = ft_strdup("");
			if (!kv->value)
				return ;//what to do if malloc fails
			kv->key = malloc(ft_strlen(*pair) - 1);
			if (!kv->key)
				return ;//what to do if malloc fails
			ft_strlcpy(kv->key, *pair, ft_strlen(*pair));
		}
		else
		{
			kv->value = ft_strdup(++value);//???
			if (!kv->value)
				return ;//what to do if malloc fails
			kv->key = malloc(ft_strlen(*pair) - ft_strlen(kv->value));
			if (!kv->key)
				return ;//what to do if malloc fails
			ft_strlcpy(kv->key, *pair, ft_strlen(*pair) - ft_strlen(kv->value));
		}
		if (!g_env)
			g_env = ft_lstnew_kv((void *)kv);
		else if (!find_key_replace_val(&g_env, kv->key, kv->value))
			ft_lstadd_back(&g_env, ft_lstnew_kv((void *)kv));
		pair++;
	}
	list = ft_merge_lists(list, g_env);
	ft_list_sort(&list, compare_key);
	while(list)
	{
		if (!arg)
		{
			write(1, "declare -x ", ft_strlen("declare -x "));
			write(1, ((t_envar *)list->content)->key, ft_strlen(((t_envar *)list->content)->key));
			if (((t_envar *)list->content)->value && *(((t_envar *)list->content)->value) != '\n')
			{
				write(1, "=", 1);
				write(1, "\"", 1);
				write(1, ((t_envar *)list->content)->value, ft_strlen(((t_envar *)list->content)->value));
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		list = list->next;
	}
	ft_lstclear(&list, free_nothing);
	//free_kv(kv, i);
}

void	ft_unset(char *arg)
{
	char **keys;
	int		first;
	t_list *tmp;
	t_list *ptr_prev;
	t_list *ptr_next;

	if (!arg)
	{
		write(1, "unset: not enough arguments", ft_strlen("unset: not enough arguments"));
		write(1, "\n", 1);
	}
	else if (ft_strchr(arg, '.') || ft_strchr(arg, '~') || ft_strchr(arg, ',') || ft_strchr(arg, '@') || ft_strchr(arg, '#') || ft_strchr(arg, '%') || ft_strchr(arg, '^') || ft_strchr(arg, '-') || ft_strchr(arg, '+') || ft_strchr(arg, '=') || ft_strchr(arg, '{') || ft_strchr(arg, '}') || ft_strchr(arg, '[') || ft_strchr(arg, ']'))
	{
		write(1, "unset: ", ft_strlen("unset: "));
		write(1, arg, ft_strlen("arg"));//HEL.L -> HEL
		write(1, ": ", ft_strlen(": "));
		write(1, "invalid parameter name", ft_strlen("invalid parameter name"));
		write(1, "\n", 1);
	}
	else
	{
		keys = ft_split(arg, ' ');//FREE
		while (keys && *keys)
		{
			tmp = g_env;
			first = 1;
			while (tmp)
			{
				if(!ft_strcmp(((t_envar *)tmp->content)->key, *keys) && !first)
				{
					ptr_next = tmp->next;
					ft_lstdelone(tmp, free_content);
					ptr_prev->next = ptr_next;
					tmp = ptr_prev;	
				}
				else if (!ft_strcmp(((t_envar *)tmp->content)->key, *keys) && first)
				{
					ptr_prev = tmp;
					ptr_next = tmp->next;
					ft_lstdelone(tmp, free_content);
					tmp = ptr_next;
					g_env = g_env->next;//COULD BE A LEAK!!!
				}
				ptr_prev = tmp;
				if (!first)
					tmp = tmp->next;
				first = 0;
			}
			keys++;
		}
	}
}

t_list	*env_to_list(char **envp)
{
	char	**env;
	char	*value;
	t_list	*list;
	t_envar	*kv;

	env = envp;
	list = NULL;
	while (*env)
	{
		kv = malloc(sizeof(t_envar));
		if (!kv)
			return (NULL);
		value = ft_strchr(*env, '=');
		value++;
		kv->key = malloc(ft_strlen(*env) - ft_strlen(value));
		if (!kv->key)
			return (NULL);
		ft_strlcpy(kv->key, *env, ft_strlen(*env) - ft_strlen(value));
		kv->value = ft_strdup(value);
		if (!kv->value)
			return (NULL);
		if (!list)
			list = ft_lstnew((void *)kv);
		else
			ft_lstadd_back(&list, ft_lstnew((void *)kv));
		env++;
	}
	return(list);
}
