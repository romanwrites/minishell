/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:33:29 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/29 20:09:46 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_unset(char *arg)
{
	char	**keys;
	int		first;
	t_list	*tmp;
	t_list	*ptr_prev;
	t_list	*ptr_next;

	if (arg)
	{
		if (ft_strchr(arg, '.') || ft_strchr(arg, '~') || ft_strchr(arg, ',') || ft_strchr(arg, '@') || ft_strchr(arg, '#') || ft_strchr(arg, '%') || ft_strchr(arg, '^') || ft_strchr(arg, '-') || ft_strchr(arg, '+') || ft_strchr(arg, '=') || ft_strchr(arg, '{') || ft_strchr(arg, '}') || ft_strchr(arg, '[') || ft_strchr(arg, ']'))
		{
			write(1, "bash: unset: `", ft_strlen("bash: unset: `"));
			write(1, arg, ft_strlen("arg"));//HEL.L -> HEL
			write(1, "\': not a valid identifier", ft_strlen("\': not a valid identifier"));
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
