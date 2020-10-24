/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 01:36:46 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/25 01:36:47 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*alloc_token_list(char **ptr)
{
	t_token	*token;
	t_token	*head;
	int		i;

	i = 0;
	token = token_new(ptr[i], NULL);
	ft_alloc_check(token);
	head = token;
	while (ptr[++i])
	{
		token->next = token_new(ptr[i], &token);
		ft_alloc_check(token->next);
		token = token->next;
	}
	return (head);
}
