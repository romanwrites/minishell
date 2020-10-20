/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:17:45 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/19 23:17:56 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	print_token_list(t_token *token)
{
	while (token)
	{
		ft_putendl_fd(token->content, 1);
		token = token->next;
	}
}