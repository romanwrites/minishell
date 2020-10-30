/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:59:28 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/30 17:59:29 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_cd(char *str)
{
	DIR		*dir;

	if (!str)
		str = get_envar("~");
	dir = opendir(str);
	if (!dir)
	{
		write(1, "cd: ", ft_strlen("cd: "));
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, ": ", ft_strlen(": "));
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		return ;
	}
	closedir(dir);
	chdir(str);
}
