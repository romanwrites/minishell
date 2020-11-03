/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sh_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 01:23:37 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/28 20:29:12 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist_sh			*process_new_node(t_dlist_sh *sh)
{
	sh->next = sh_new(NULL, NULL);
	sh = sh->next;
	return (sh);
}

void				*free_sh(t_dlist_sh *sh, char **tmp_semi, t_token *tmp_tok)
{
	t_dlist_sh		*tmp_sh;
	t_dlist_pipe	*tmp_pipe;

	while (sh)
	{
		while (sh->tdlst_pipe)
		{
			while (sh->tdlst_pipe_head->token)
			{
				if (sh->tdlst_pipe_head->token->content)
					free(sh->tdlst_pipe_head->token_head->content);
				tmp_tok = sh->tdlst_pipe_head->token;
				sh->tdlst_pipe_head->token = sh->tdlst_pipe_head->token->next;
				free(tmp_tok);
			}
			tmp_pipe = sh->tdlst_pipe_head;
			sh->tdlst_pipe_head = sh->tdlst_pipe_head->next;
			free(tmp_pipe);
		}
		tmp_sh = sh;
		sh = sh->prev;
		free(tmp_sh);
	}
	ft_free2d(tmp_semi);
	return (NULL);
}

t_dlist_sh			*get_sh_list(char **semicolons2d, int i, t_mshell *sv)
{
	t_dlist_pipe	*dlst_pipe;
	t_dlist_sh		*sh;
	t_dlist_sh		*sh_head;
	char			**tmp_semi;

	sh = sh_new(NULL, NULL);
	sh_head = sh;
	sv->sh_head = sh_head;
	while (semicolons2d[i])
	{
		tmp_semi = split_by_char(PIPE, semicolons2d[i]);
		if (check_syntax_2d(tmp_semi))
			return (free_sh(sh, tmp_semi, NULL));
		if (!(dlst_pipe = alloc_pipe_list(tmp_semi, 0)))
			return (free_sh(sh, tmp_semi, NULL));
		ft_free2d(tmp_semi);
		sh->tdlst_pipe = dlst_pipe;
		if (semicolons2d[i + 1])
			sh = process_new_node(sh);
		i++;
	}
	return (sh_head);
}
