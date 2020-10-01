/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelmid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 21:45:47 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/01 18:45:16 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Takes as a parameter an elem and frees the memory of the elem’s content
** using the function ’del’ given as a parameter and free the elem.
** The memory of ’next’ must not be freed.
*/

void	ft_lstdelmid(t_list *lst, void (*del)(void*))
{
	t_list *tmp;

	if (!lst || !del)
		return ;
	del(lst->content);
	tmp = lst;
	lst = lst->next;
	free(tmp);
}
