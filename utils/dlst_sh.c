/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 18:50:27 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/19 18:51:08 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist_sh		*ft_dlst_sh_new(t_token *content, t_dlist_sh **prev)
{
	t_dlist_sh	*new;

	if (!(new = malloc(sizeof(t_dlist_sh))))
		return (NULL);
	new->token_lst = content;
	if (prev)
		new->prev = *prev;
	else
		new->prev = NULL;
	new->next = NULL;
	return (new);
}
