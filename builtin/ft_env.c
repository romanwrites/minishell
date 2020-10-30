/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:01:02 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/30 18:01:03 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_env(void)
{
	t_list	*env;

	env = g_env;
	while (env)
	{
		if (((t_envar *)env->content)->value)
		{
			ft_putstr_fd(((t_envar *)env->content)->key, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(((t_envar *)env->content)->value, 1);
		}
		env = env->next;
	}
}
