/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:33:29 by lhelper           #+#    #+#             */
/*   Updated: 2020/11/03 16:07:34 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static _Bool	is_invalid_char_unset(char *arg)
{
	size_t		len;
	size_t		i;

	len = ft_strlen(".~,@#%^-+={}[]");
	i = 0;
	while (i < len)
	{
		if ((ft_strchr(arg, ".~,@#%^-+={}[]"[i])))
			return (1);
		i++;
	}
	if (!ft_strcmp(g_home, arg))
		return (1);
	return (0);
}

static void		put_not_a_valid_identifier(char *arg)
{
	ft_putstr_fd("bash: unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
	g_exit = 1;
}

static	int		check_args(char **arg)
{
	int i;

	i = 1;
	while (arg[i])
	{
		if (is_invalid_char_unset(arg[i]))
		{
			put_not_a_valid_identifier(arg[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static void		del_node(t_prevnext *pn, char **keys)
{
	if (!ft_strcmp(((t_envar *)pn->tmp->content)->key, *keys) && !pn->first)
	{
		pn->ptr_next = pn->tmp->next;
		ft_lstdelone(pn->tmp, free_content);
		pn->ptr_prev->next = pn->ptr_next;
		pn->tmp = pn->ptr_prev;
	}
	else if (!ft_strcmp(((t_envar *)pn->tmp->content)->key, *keys) && pn->first)
	{
		pn->ptr_prev = pn->tmp;
		pn->ptr_next = pn->tmp->next;
		ft_lstdelone(pn->tmp, free_content);
		pn->tmp = pn->ptr_next;
		g_env = g_env->next;//COULD BE A LEAK!!!
	}
	pn->ptr_prev = pn->tmp;
	if (!pn->first)
		pn->tmp = pn->tmp->next;
	pn->first = 0;
}

void			ft_unset(char **arg)
{
	char		**keys;
	t_prevnext	*pn;

	keys = arg;
	keys++;
	if (arg[1])
	{
		if (check_args(arg))
			return ;
		while (keys && *keys)
		{
			pn->tmp = g_env;
			pn->first = 1;
			while (pn->tmp)
				del_node(pn, keys);
			keys++;
		}
	}
}
