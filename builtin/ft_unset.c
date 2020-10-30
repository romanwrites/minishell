/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:33:29 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/30 19:14:56 by lhelper          ###   ########.fr       */
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
	return (0);
}

static void		put_not_a_valid_identifier(char *arg)
{
	ft_putstr_fd("bash: unset: `", 1);
	ft_putstr_fd(arg, 1);
	ft_putendl_fd("\': not a valid identifier", 1);
}

void			ft_unset(char *arg)
{
	char		**keys;
	int			first;
	t_list		*tmp;
	t_list		*ptr_prev;
	t_list		*ptr_next;

	if (arg)
	{
		if (is_invalid_char_unset(arg))
			put_not_a_valid_identifier(arg);
		else
		{
			keys = ft_split(arg, ' ');//FREE
			while (keys && *keys)
			{
				tmp = g_env;
				first = 1;
				while (tmp)
				{
					if (!ft_strcmp(((t_envar *)tmp->content)->key, *keys) && !first)
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
}
