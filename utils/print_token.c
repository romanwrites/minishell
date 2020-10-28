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
		ft_putstr_fd("is_diff: ", 1);
		char c = token->is_diff + '0';
		write(1, &c, 1);
		write(1, "\n", 1);
		token = token->next;
	}
}
