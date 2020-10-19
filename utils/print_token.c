/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:17:45 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/19 23:17:56 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	print_token(t_token *token)
{
	while (token)
	{
		ft_putstr_fd(token->content, 1);
		token = token->next;
	}
}