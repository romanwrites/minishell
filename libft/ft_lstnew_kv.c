/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_kv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 00:20:01 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/01 16:55:47 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/minishell.h"

/*
** Allocates (with malloc(3)) and returns a new element.
** content is initialized with the value of the parameter ’content’.
** The variable ’next’ is initialized to NULL
*/

t_list		*ft_lstnew_kv(void *content)
{
	t_list	*new;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	new->content = malloc(sizeof(content));
	new->content = ft_memcpy(new->content, content, sizeof(content));
	if (!(((t_envar *)new->content)->key = ft_strdup(((t_envar *)content)->key)))
		return (NULL);
	if (!(((t_envar *)new->content)->value = ft_strdup(((t_envar *)content)->value)))
		return (NULL);
	new->next = NULL;
	return (new);
}
