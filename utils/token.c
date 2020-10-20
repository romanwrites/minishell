/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 18:50:32 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/19 18:50:33 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*token_new(char *content, t_token **prev)
{
	t_token	*new;

	if (!(new = malloc(sizeof(t_token))))
		return (NULL);
	new->content = content;
	if (prev)
		new->prev = *prev;
	else
		new->prev = NULL;
	new->next = NULL;
	return (new);
}