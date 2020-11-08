/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:21:57 by mkristie          #+#    #+#             */
/*   Updated: 2020/11/06 14:09:16 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_kv(t_envar *kv)
{
	free(kv->value);
	free(kv->key);
	free(kv);
}

void		process_list(t_list *list, const char *arg)
{
	t_list *to_free;

	ft_list_sort(&list, compare_key);
	to_free = list;
	while (list)
	{
		if (!arg || *arg == '|' || *arg == '>' || *arg == '<')
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(((t_envar *)list->content)->key, 1);
			if (((t_envar *)list->content)->value && \
				*(((t_envar *)list->content)->value) != '\n')
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(((t_envar *)list->content)->value, 1);
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		list = list->next;
	}
	ft_lstclear(&to_free, free_nothing);
}

static void	add_kv_to_env(t_envar *kv)
{
	t_envar	*tmp;

	tmp = kv;
	if (!g_env)
		g_env = ft_lstnew_kv_n_chk((void *)tmp);
	else if (!find_key_replace_val(&g_env, tmp->key, tmp->value))
		ft_lstadd_back(&g_env, ft_lstnew_kv_n_chk((void *)tmp));
}

void		process_pair(char **pair, t_envar *kv, char *value)
{
	while (pair && *pair)
	{
		kv = malloc_n_chk(sizeof(t_envar));
		value = ft_strchr(*pair, '=');
		if (!value)
		{
			kv->value = NULL;
			kv->key = ft_strdup_and_check(*pair);
		}
		else if (*(value + 1) == '\0')
		{
			kv->value = ft_strdup_and_check("");
			kv->key = malloc_n_chk(ft_strlen(*pair) - 1);
			ft_strlcpy(kv->key, *pair, ft_strlen(*pair));
		}
		else
		{
			kv->value = ft_strdup_and_check(++value);
			kv->key = malloc_n_chk(ft_strlen(*pair) - ft_strlen(kv->value));
			ft_strlcpy(kv->key, *pair, ft_strlen(*pair) - ft_strlen(kv->value));
		}
		add_kv_to_env(kv);
//		free_kv(kv);
		pair++;
	}
}

void		ft_export(char **arg)
{
	t_list	*list;
	t_envar	*kv;
	char	*value;
	char	**args;

	kv = NULL;
	value = NULL;
	list = NULL;
	args = arg;
	args++;
	process_pair(args, kv, value);
	list = ft_merge_lists(list, g_env);
	process_list(list, arg[1]);
}
