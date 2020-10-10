/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelmid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 21:45:47 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/04 16:54:05 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
