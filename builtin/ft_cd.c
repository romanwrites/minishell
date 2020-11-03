/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:59:28 by mkristie          #+#    #+#             */
/*   Updated: 2020/11/03 14:08:42 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_cd(char *str)
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
			write(2, "bash: cd: OLDPWD not set\n", ft_strlen("bash: cd: OLDPWD not set\n"));
			g_exit = 1;
			return ;
		}
		flag = 1;
	}
	dir = opendir(str);
	if (!dir)
	{
		write(2, "cd: ", ft_strlen("cd: "));
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", ft_strlen(": "));
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		return ;
	}
	closedir(dir);
	chdir(str);
	refresh_env();
	if (flag)
		ft_pwd();
}
