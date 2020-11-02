/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:28:24 by mkristie          #+#    #+#             */
/*   Updated: 2020/11/02 19:44:01 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static _Bool	put_g_exit(void)
{
	char		*str;

	str = ft_itoa_and_chk(g_exit);
	ft_putendl_fd(str, 1);
	free(str);
	return (1);
}

static void		process_with_flag(char **cmd, int i)
{
	if (cmd[i])
	{
		if (!(ft_strcmp(cmd[i], "$?")) && put_g_exit())
			return ;
		while (cmd[i])
		{
			write(1, cmd[i], ft_strlen(cmd[i]));
			if (cmd[i + 1] && (cmd[i + 1][0] == 0 || cmd[i][0] == 0))
			{
				i++;
				continue;
			}
			if (cmd[i + 1] && cmd[i + 1][0] != 0 && cmd[i][0] != 0)
				write(1, " ", 1);
			i++;
		}
	}
	else
		write(1, "\n", 1);
}

void			ft_echo(char **cmd)
{
	int			i;
	int			is_n;

	i = 1;
	is_n = 0;
	if (cmd[i])
	{
		while(cmd[i] && !(ft_strcmp(cmd[i], "-n")))
		{
			is_n = 1;
			i++;
		}
		if (is_n)
			process_with_flag(cmd, i);
		else
		{
			if (!(ft_strcmp(cmd[i], "$?")) && put_g_exit())
				return ;
			while (cmd[i])
			{
				write(1, cmd[i], ft_strlen(cmd[i]));
				if ((cmd[i + 1] && cmd[i + 1][0] == 0) || cmd[i][0] == 0)
				{
					i++;
					continue;
				}
				if (cmd[i + 1])
					write(1, " ", 1);
				else
					write(1, "\n", 1);
				i++;
			}
		}
	}
	else
		write(1, "\n", 1);
}
