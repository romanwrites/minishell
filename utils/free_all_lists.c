/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:09:09 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/28 20:32:30 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_token_lst(t_token *token)
{
	t_token *tmp;

	while (token)
	{
		if (token->content)
		{
			free(token->content);
			token->content = NULL;
		}
		tmp = token;
		token = token->next;
		free(tmp);
		tmp = NULL;
	}
}

void		free_all_lists(t_mshell *sv)
{
	int 	pipe = 0, tok = 0, semi = 0;
	t_dlist_pipe	*tmp_pipe;
	t_dlist_sh		*tmp_sh;

    sv->sh = sv->sh_head;
	while (sv->sh)
	{
		pipe = 0;
		sv->sh->tdlst_pipe = sv->sh->tdlst_pipe_head;
		while (sv->sh->tdlst_pipe)
		{
			free_token_lst(sv->sh->tdlst_pipe->token_head);
			tmp_pipe = sv->sh->tdlst_pipe;
			sv->sh->tdlst_pipe = sv->sh->tdlst_pipe->next;
			free(tmp_pipe);
			tmp_pipe = NULL;
			++pipe;
		}
		tmp_sh = sv->sh;
		sv->sh = sv->sh->next;
		free(tmp_sh);
		tmp_sh = NULL;
		++semi;
	}
}
