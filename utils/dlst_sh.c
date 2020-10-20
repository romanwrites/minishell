/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:09:01 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/19 23:09:03 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist_sh		*sh_new(t_dlist_pipe *content, t_dlist_sh **prev)
{
	t_dlist_sh	*new;

	if (!(new = malloc(sizeof(t_dlist_sh))))
		return (NULL);
	new->tdlst_pipe = content;
	if (prev)
		new->prev = *prev;
	else
		new->prev = NULL;
	new->next = NULL;
	return (new);
}
