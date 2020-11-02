/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:52:36 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/30 17:52:39 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_exit(char **cmd)
{
	int		minus;

	minus = 0;
	write(2, "exit\n", ft_strlen("exit\n"));
	if (!cmd || !cmd[1])
		exit((int)g_exit % 256);
	if (cmd[2])
	{
		ft_putendl_fd("bash: exit: too many arguments", 1);
		return ;
	}
	ft_atoull(cmd[1], &minus);
	if (check_numeric(cmd[1]) || \
		((!minus && ft_atoull(cmd[1], &minus) > __LONG_LONG_MAX__) || \
		(minus && ft_atoull(cmd[1], &minus) - 1 > __LONG_LONG_MAX__)))
	{
		ft_putstr_fd("bash: exit: ", 1);
		ft_putstr_fd(cmd[1], 1);
		ft_putendl_fd(": numeric argument required", 1);
		exit(255);
	}
	exit((int)(ft_atoll(cmd[1]) % 256));
}
