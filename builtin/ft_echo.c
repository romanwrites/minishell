/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:28:24 by mkristie          #+#    #+#             */
/*   Updated: 2020/11/03 18:53:23 by lhelper          ###   ########.fr       */
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
	int is_n;

	if (cmd[i])
	{
		if (!(ft_strcmp(cmd[i], "$?")) && put_g_exit())
			return ;
		is_n = i;
		while (cmd[i])
		{
			write(1, cmd[i], ft_strlen(cmd[i]));
			if ((cmd[i + 1] && cmd[i + 1][0] == 0) || \
			(cmd[i][0] == 0 && is_n == i))
			{
				i++;
				continue;
			}
			if (cmd[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
}

int				skip_repeat(char **cmd, int *i)
{
	int is_n;

	is_n = 0;
	while (cmd[*i] && !(ft_strcmp(cmd[*i], "-n")))
	{
		is_n = 1;
		(*i)++;
	}
	return (is_n);
}

void			print_echo(char **cmd, int i, int is_n)
{
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if ((cmd[i + 1] && cmd[i + 1][0] == 0) || \
		(cmd[i][0] == 0 && is_n == i))
		{
			if (!cmd[i + 1])
			{
				write(1, "\n", 1);
				return ;
			}
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

void			ft_echo(char **cmd)
{
	int			i;
	int			is_n;

	i = 1;
	is_n = 0;
	if (cmd[i])
	{
		if ((is_n = skip_repeat(cmd, &i)))
			process_with_flag(cmd, i);
		else
		{
			if (!(ft_strcmp(cmd[i], "$?")) && put_g_exit())
				return ;
			is_n = i;
			print_echo(cmd, i, is_n);
		}
	}
	else
		write(1, "\n", 1);
}
