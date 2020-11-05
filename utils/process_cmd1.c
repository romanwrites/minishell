/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 17:08:01 by lhelper           #+#    #+#             */
/*   Updated: 2020/11/05 17:11:44 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		add_token(t_norma *n, t_token *token)
{
	n->cmd[(n->i)++] = token->content;
	n->cmd[n->i] = NULL;
}

t_token		*next_pipe(t_mshell *sv)
{
	t_token *tmp;

	tmp = sv->sh->tdlst_pipe->token_head;
	sv->sh->tdlst_pipe = sv->sh->tdlst_pipe->next;
	return (tmp);
}

void		next_semicolon(t_mshell *sv)
{
	sv->sh->tdlst_pipe = sv->sh->tdlst_pipe_head;
	sv->sh = sv->sh->next;
}

void		execute_child(t_norma *n)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	close(n->fds[0]);
	dup2(n->fds[1], 1);
	close(n->fds[1]);
	execute_command(n->cmd, n->fdr, n->fdl);
	exit((int)g_exit % 256);
}

void		execute_parent(t_norma *n)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	wait(NULL);
	signal(SIGQUIT, handle_parent_signal);
	signal(SIGINT, handle_parent_signal);
	close(n->fds[1]);
	dup2(n->fds[0], 0);
	close(n->fds[0]);
	n->fdr = -2;
	n->fdl = -2;
}
