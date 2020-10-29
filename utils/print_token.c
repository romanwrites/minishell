/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:39:13 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/29 18:39:14 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_token_list(t_token *token)
{
	char	c;

	while (token)
	{
		ft_putendl_fd(token->content, 1);
		ft_putstr_fd("is_diff: ", 1);
		c = token->is_diff + '0';
		write(1, &c, 1);
		write(1, "\n", 1);
		token = token->next;
	}
}
