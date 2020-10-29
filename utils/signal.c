/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 18:31:10 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/28 20:38:49 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parent_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(0, "\b\b  \b\b", 6);
		write(0, "\n", 1);
		write(0, PROMPT, ft_strlen(PROMPT));
		g_exit = 1;
	}
	else
		write(0, "\b\b  \b\b", 6);
}
