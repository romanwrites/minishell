/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:21:57 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/30 18:22:00 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		process_list(t_list *list, const char *arg)
{
	ft_list_sort(&list, compare_key);
	while (list)
	{
		if (!arg)
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
	ft_lstclear(&list, free_nothing);
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
		if (!g_env)
			g_env = ft_lstnew_kv_n_chk((void *)kv);
		else if (!find_key_replace_val(&g_env, kv->key, kv->value))
			ft_lstadd_back(&g_env, ft_lstnew_kv_n_chk((void *)kv));
		pair++;
	}
}

void		ft_export(char *arg)
{
	t_list	*list;
	t_envar	*kv;
	char	**pair;
	char	*value;

	kv = NULL;
	value = NULL;
	list = NULL;
	pair = ft_split_n_chk(arg, ' ');
	process_pair(pair, kv, value);
	list = ft_merge_lists(list, g_env);
	process_list(list, arg);
}
