/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:22:06 by lhelper           #+#    #+#             */
/*   Updated: 2020/11/03 18:35:52 by lhelper          ###   ########.fr       */
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

void		refresh_env(void)
{
	char	*pwd;
	char	*old;
	char	*test[3];

	test[0] = "command";
	test[1] = "OLDPWD";
	test[2] = NULL;
	pwd = get_envar("PWD");
	if (!pwd)
		pwd = ft_strdup("");
	set_oldpwd(old, pwd, test);
	set_pwd(old, test);
}
