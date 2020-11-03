/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:22:06 by lhelper           #+#    #+#             */
/*   Updated: 2020/11/03 17:15:24 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_oldpwd(char *old, char *pwd, char **test)
{
	t_list	*env;
	int		flag;

	env = g_env;
	flag = 0;
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
}

static void	set_pwd(char *old, char **test)
{
	t_list	*env;

	env = g_env;
	while (env)
	{
		if (!ft_strcmp(((t_envar *)(env->content))->key, "PWD"))
		{
			old = ((t_envar *)(env->content))->value;
			((t_envar *)(env->content))->value = malloc(PATH_MAX);
			free(old);
			ft_alloc_check(((t_envar *)(env->content))->value);
			((t_envar *)(env->content))->value = \
			getcwd(((t_envar *)(env->content))->value, PATH_MAX);
		}
		env = env->next;
	}
}

void	refresh_env(void)
{
	//t_list	*env;
	char	*pwd;
	char	*old;
	char	*test[] = {"unset", "OLDPWD", NULL};

	pwd = get_envar("PWD");
	//env = g_env;
	set_oldpwd(old, pwd, test);
	/*
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
	*/
	//env = g_env;
	set_pwd(old, test);
	/*
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
	*/
}
