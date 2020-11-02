/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:00:34 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/28 20:36:18 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ret_value(char *value)
{
	char	*ret;

	ret = ft_strdup_and_check(value);
	return (ret);
}

int			handle_if_tilda(char **var)
{
	*var = ft_strdup_and_check("HOME");
	return (1);
}

char		*free_and_g_home(char **var)
{
	free(*var);
	return (g_home);
}

char		*get_envar(char *var)
{
	t_list	*env;
	char	*ret;
	int		flag;

	env = g_env;
	flag = 0;
	if (!ft_strcmp(var, "?"))
		return (ft_itoa_and_chk((int)g_exit % 256));
	if (!ft_strcmp(var, "~"))
		flag = handle_if_tilda(&var);
	while (env)
	{
		if (!ft_strcmp(((t_envar *)(env->content))->key, var))
		{
			ret = ret_value(((t_envar *)(env->content))->value);
			if (flag)
				free(var);
			return (ret);
		}
		env = env->next;
	}
	if (flag)
		return (free_and_g_home(&var));
	return (NULL);
}
