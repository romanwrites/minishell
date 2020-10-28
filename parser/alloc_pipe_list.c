/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_pipe_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 01:35:35 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/28 20:01:05 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist_pipe		*alloc_pipe_list(char **ptr, int i)
{
	char			**tmp_cmd;
	char			**trim_cmd;
	t_token			*token;
	t_dlist_pipe	*pipe;
	t_dlist_pipe	*head;

	pipe = pipe_new(NULL, NULL);
	head = pipe;
	while (ptr[i])
	{
		if (!(tmp_cmd = split_command(ptr[i])))
			return (NULL);
		trim_cmd = ft_trim_2d_cpy(tmp_cmd);
		token = alloc_token_list(trim_cmd);
		ft_free2d(trim_cmd);
		tmp_cmd = NULL;
		pipe->token = token;
		if (ptr[i + 1])
		{
			pipe->next = pipe_new(NULL, &pipe);
			pipe = pipe->next;
		}
		i++;
	}
	return (head);
}
