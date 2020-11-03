/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:59:28 by mkristie          #+#    #+#             */
/*   Updated: 2020/11/03 17:31:22 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		throw_error(char *str)
{
	write(2, "cd: ", ft_strlen("cd: "));
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, ": ", ft_strlen(": "));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	g_exit = 1;
}

static void		pwd_error(void)
{
	ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
	g_exit = 1;
}

static void		close_change_refresh(DIR *dir, char *str, int flag)
{
	closedir(dir);
	chdir(str);
	refresh_env();
	if (flag)
		ft_pwd();
}

void			ft_cd(char *str)
{
	DIR		*dir;
	int		flag;

	flag = 0;
	if (!str)
		str = get_envar("~");
	else if (!ft_strcmp(str, "-"))
	{
		str = get_envar("OLDPWD");
		if (!str)
		{
			pwd_error();
			return ;
		}
		flag = 1;
	}
	dir = opendir(str);
	if (!dir)
	{
		throw_error(str);
		return ;
	}
	close_change_refresh(dir, str, flag);
}
