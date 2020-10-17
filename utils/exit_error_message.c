/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error_message.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 22:23:06 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/29 22:24:21 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exit_error_message(char *str) // maybe set exit_code somewhere here also
{
	ft_putstr_fd(str, 2); //2 fd?

//	exit(2);
}