/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:09:23 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/29 18:09:24 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates (with malloc(3)) and returns a new element.
** content is initialized with the value of the parameter ’content’.
** The variable ’next’ is initialized to NULL
*/

t_dlist		*ft_dlstnew(void *content, t_dlist **prev)
{
	t_dlist	*new;

	if (!(new = malloc(sizeof(t_dlist))))
		return (NULL);
	new->content = content;
	if (prev)
		new->previous = *prev;
	else
		new->previous = NULL;
	new->next = NULL;
	return (new);
}
