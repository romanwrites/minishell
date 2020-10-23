/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 18:31:10 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/23 18:39:27 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_parent_with_child(int signal)
{
	if(signal == SIGINT)
	{
		write(0, "\n", 1);
		g_exit = 130;
	}
	else if (SIGQUIT == signal)
	{
		if (!input)
		{
			free(input);
			input = NULL;
			write(0, "Quit: 3", ft_strlen("Quit: 3"));
			write(0, "\n", 1);
			g_exit = 131;
		}
	}
}

void	handle_parent_signal(int signal)
{
	if (!g_isfork)
	{
		if(signal == SIGINT)
		{
			write(0, "\b\b  \b\b", 6);
			write(0, "\n", 1);
			write(0, PROMPT, ft_strlen(PROMPT));
			g_exit = 1;
		}
		else
			write(0, "\b\b  \b\b", 6);
	}
	else
		handle_parent_with_child(signal);
}

void    handle_child_signal(int signal)
{
    if(signal == SIGINT)
        exit(130);
    if (signal == SIGQUIT)
        exit(131);
}