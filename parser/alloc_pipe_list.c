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

static void			*free_prev_pipes(t_dlist_pipe *pipe)
{
	t_dlist_pipe	*tmp;
	t_token			*tmp_token;

	tmp = pipe;
	while (pipe)
	{
		if (pipe->token)
		{
			while (pipe->token)
			{
				if (pipe->token->content)
					free(pipe->token->content);
				tmp_token = pipe->token;
				pipe->token = pipe->token->next;
				free(tmp_token);
			}
		}
		tmp = pipe;
		pipe = pipe->prev;
		free(tmp);
	}
	return (NULL);
}

t_dlist_pipe		*alloc_pipe_list(char **ptr, int i)
{
	char			**tmp_cmd;
	t_token			*token;
	t_dlist_pipe	*pipe;
	t_dlist_pipe	*head;

	pipe = pipe_new(NULL, NULL);
	head = pipe;
	while (ptr[i])
	{
		if (!(tmp_cmd = split_command(ptr[i])))
			return (free_prev_pipes(pipe));
		token = alloc_token_list(tmp_cmd);
		ft_free2d(tmp_cmd);
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
