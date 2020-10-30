/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:48:57 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/30 17:49:02 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_pwd(void)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
}
