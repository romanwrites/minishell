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

t_token			*alloc_token_list(char **ptr)
{
	t_token		*token;
	t_token		*head;
	char		*str_dup;
	int			i;

	i = 0;
	str_dup = ft_strdup_and_check(ptr[i]);
	token = token_new(str_dup, NULL);
	head = token;
	while (ptr[++i])
	{
		str_dup = ft_strdup_and_check(ptr[i]);
		token->next = token_new(str_dup, &token);
		str_dup = NULL;
		token = token->next;
	}
	return (head);
}
