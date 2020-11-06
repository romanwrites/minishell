/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:11:41 by mkristie          #+#    #+#             */
/*   Updated: 2020/11/06 10:54:07 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_nothing(void *to_free)
{
	t_envar *content;

	content = to_free;
}

void		free_content(void *to_free)
{
	t_envar *content;

	content = to_free;
	free(content->key);
	free(content->value);
}

t_list		*ft_merge_lists(t_list *dst, t_list *src)
{
	t_list	*t_dst;
	t_list	*t_src;

	if (src == NULL)
		return (dst);
	t_dst = dst;
	t_src = src;
	while (t_src)
	{
		if (!t_dst)
			t_dst = ft_lstnew_n_chk(t_src->content);
		else
			ft_lstadd_back(&t_dst, ft_lstnew_n_chk(t_src->content));
		t_src = t_src->next;
	}
	return (t_dst);
}

int			find_key_replace_val(t_list **lst, char *key, char *value)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (!ft_strcmp(((t_envar *)tmp->content)->key, key))
		{
			free(((t_envar *)tmp->content)->value);
			((t_envar *)tmp->content)->value = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_list		*env_to_list(char **envp)
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
		ft_alloc_check(kv);
		value = ft_strchr(*env, '=');
		value++;
		kv->key = malloc(ft_strlen(*env) - ft_strlen(value));
		ft_alloc_check(kv->key);
		ft_strlcpy(kv->key, *env, ft_strlen(*env) - ft_strlen(value));
		kv->value = ft_strdup_and_check(value);
		if (!list)
			list = ft_lstnew_n_chk((void *)kv);
		else
			ft_lstadd_back(&list, ft_lstnew_n_chk((void *)kv));
		env++;
	}
	return (list);
}
