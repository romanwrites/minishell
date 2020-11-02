/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 18:50:32 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/28 20:44:54 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*token_new(char *content, t_token **prev)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	ft_alloc_check(new);
	new->content = content;
	if (prev)
		new->prev = *prev;
	else
		new->prev = NULL;
	new->next = NULL;
	return (new);
}
