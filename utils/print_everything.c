/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_everything.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:20:15 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/20 13:20:17 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_everything(t_mshell *sv)
{
	t_token	*token;

	while (sv->sh)
	{
		while (sv->sh->tdlst_pipe)
		{
			open_quotes(sv->sh->tdlst_pipe->token);
			token = sv->sh->tdlst_pipe->token_head;
			print_token_list(token);
			sv->sh->tdlst_pipe = sv->sh->tdlst_pipe->next;
		}
		sv->sh = sv->sh->next;
	}
}
