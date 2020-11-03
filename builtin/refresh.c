/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:22:06 by lhelper           #+#    #+#             */
/*   Updated: 2020/11/03 16:47:28 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	refresh_env(void)
{
	t_list	*env;
	char	*pwd;
	char	*old;
	int		flag;
	char	*test[] = {"unset", "OLDPWD", NULL};

	flag = 0;
	pwd = get_envar("PWD");
	env = g_env;
	while (env)
	{
		if (!ft_strcmp(((t_envar *)(env->content))->key, "OLDPWD"))
		{
			old = ((t_envar *)(env->content))->value;
			((t_envar *)(env->content))->value = ft_strdup(pwd);
			free(old);
			flag = 1;
		}
		env = env->next;
	}
	if (!flag)
	{
		test[1] = ft_strjoin("OLDPWD=", pwd);
		ft_export(test);
		free(test[1]);
	}
	free(pwd);
	env = g_env;
	while (env)
	{
		if (!ft_strcmp(((t_envar *)(env->content))->key, "PWD"))
		{
			old = ((t_envar *)(env->content))->value;
			((t_envar *)(env->content))->value = malloc(PATH_MAX);
			if (!((t_envar *)(env->content))->value)
			{
				printf("malloc failed!\n");
				free(old);
				exit(1);
			}
			((t_envar *)(env->content))->value = \
			getcwd(((t_envar *)(env->content))->value, PATH_MAX);
			free(old);
		}
		env = env->next;
	}
}
