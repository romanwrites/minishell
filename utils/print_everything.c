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

void		print_everything()
{
	t_token *token;
	
	while (g_sv->sh)
	{
		while (g_sv->sh->tdlst_pipe)
		{
			g_sv->sh->tdlst_pipe->token_head = g_sv->sh->tdlst_pipe->token;
			while (g_sv->sh->tdlst_pipe->token)
			{
				token = g_sv->sh->tdlst_pipe->token;
				open_quotes(&token);
				g_sv->sh->tdlst_pipe->token = g_sv->sh->tdlst_pipe->token->next;
			}
			token = g_sv->sh->tdlst_pipe->token_head;
			print_token_list(token);
			g_sv->sh->tdlst_pipe = g_sv->sh->tdlst_pipe->next;
		}
		g_sv->sh = g_sv->sh->next;
	}
}