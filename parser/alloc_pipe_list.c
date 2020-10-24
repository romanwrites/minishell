/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_pipe_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 01:35:35 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/25 01:35:36 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist_pipe	*alloc_pipe_list(char **ptr)
{
	int 		i;
	char 		**tmp_cmd;
	char 		**trim_cmd;
	t_token		*token;
	t_dlist_pipe	*pipe;
	t_dlist_pipe	*head;

	i = 0;
	tmp_cmd = NULL;
	pipe = pipe_new(NULL, NULL);
	ft_alloc_check(pipe);
	head = pipe;
	while (ptr[i])
	{
		tmp_cmd = split_command(ptr[i]);
		ft_alloc_check(tmp_cmd);
		trim_cmd = ft_trim_2d_cpy(tmp_cmd);
		token = alloc_token_list(trim_cmd);
		ft_alloc_check(token);
		ft_free2d(tmp_cmd);
		tmp_cmd = NULL;
		pipe->token = token;
		if (ptr[i + 1])
		{
			pipe->next = pipe_new(NULL, &pipe);
			ft_alloc_check(pipe->next);
			pipe = pipe->next;
		}
		i++;
	}
	return (head);
}