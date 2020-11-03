/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:52:27 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/30 17:46:03 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		status_return(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			write(1, "\n", 1);
			return (130);
		}
		if (WTERMSIG(status) == 3)
		{
			write(1, "Quit: 3\n", ft_strlen("Quit: 3\n"));
			return (131);
		}
		if (WTERMSIG(status) == 15)
			return (143);
	}
	return (WEXITSTATUS(status));
}
