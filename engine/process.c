/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:30:21 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/21 19:28:11 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		process_cmd()
{
	t_token *token;
	char **cmd;
    
    cmd = (char **)malloc((sizeof(char *) * PATH_MAX));
    int i = 0;
	while (g_sv->sh)
	{
		while (g_sv->sh->tdlst_pipe)
		{
			g_sv->sh->tdlst_pipe->token_head = g_sv->sh->tdlst_pipe->token;
			while (g_sv->sh->tdlst_pipe->token)
			{
				token = g_sv->sh->tdlst_pipe->token;
				open_quotes(&token);
                if ((!ft_strcmp(token->content, ">") || !ft_strcmp(token->content, ">>") || !ft_strcmp(token->content, "<") && token->is_diff && token->next && token->next->content && (ft_strcmp(token->next->content, ">") && ft_strcmp(token->next->content, ">>") && ft_strcmp(token->next->content, "<"))))
                    execute_command(cmd);
                else
                {
                        
                }    
				g_sv->sh->tdlst_pipe->token = g_sv->sh->tdlst_pipe->token->next;
			}
			token = g_sv->sh->tdlst_pipe->token_head;
			//print_token_list(token);
			//printf("semi: %d, pipe: %d, tok: %d\n", semi, pipe, ++tok);
			g_sv->sh->tdlst_pipe = g_sv->sh->tdlst_pipe->next;
		}
		g_sv->sh = g_sv->sh->next;
	}
}