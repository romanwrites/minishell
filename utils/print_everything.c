/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_everything.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:20:15 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/27 16:40:26 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_everything(t_mshell *sv)
{
	t_token	*token;
	int 	pipe = 0;
	int		tok = 0;
	int 	semi = 0;

	while (sv->sh)
	{
		pipe = 0;
		while (sv->sh->tdlst_pipe)
		{
			sv->sh->tdlst_pipe->token_head = sv->sh->tdlst_pipe->token;
			open_quotes(sv->sh->tdlst_pipe->token);
			token = sv->sh->tdlst_pipe->token_head;
			print_token_list(token);
			printf("semi: %d, pipe: %d, tok: %d\n", semi, pipe, ++tok);//todo
			sv->sh->tdlst_pipe = sv->sh->tdlst_pipe->next;
			++pipe;
		}
		sv->sh = sv->sh->next;
		++semi;
	}
}
