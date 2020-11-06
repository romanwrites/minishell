/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:30:21 by lhelper           #+#    #+#             */
/*   Updated: 2020/11/06 14:14:27 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool	g_bp;

void		timer(void)
{
	if (g_exit && !g_timer)
		g_timer = 1;
	if (g_timer)
	{
		g_timer--;
		if (!g_timer)
			g_exit = 0;
	}
}

void		init_vars(t_norma *n)
{
	n->cmd = (char **)malloc((sizeof(char *) * PATH_MAX));
	ft_alloc_check(n->cmd);
	n->fdl = -2;
	n->fdr = -2;
	n->savestdin = dup(0);
	n->savestdout = dup(1);
}

void		execute_pipe(t_norma *n, t_mshell *sv)
{
	if (sv->sh->tdlst_pipe->next)
	{
		preexecute_pipe(n);
		if (n->pid == 0)
			execute_child(n);
		else
			execute_parent(n);
	}
	else
	{
		execute_command(n->cmd, n->fdr, n->fdl);
		dup2(n->savestdin, 0);
		dup2(n->savestdout, 1);
	}
}

_Bool		process_token(t_norma *n, t_token *token)
{
	while (token)
	{
		if ((check_redirs_only(token->content) && token->is_diff && \
		token->next && (!check_redirs_only(token->next->content))))
		{
			left_or_right(n, token);
			if (n->fdr == -1 || n->fdl == -1)
			{
				print_no_file_dir(token->next->content);
				free(n);
				return (0);
			}
			token = token->next;
		}
		else
			add_token(n, token);
		token = token->next;
	}
	return (1);
}

void		process_cmd(t_mshell *sv)
{
	t_token *token;
	t_norma	*n;

	n = malloc(sizeof(t_norma));
	init_vars(n);
	while (sv->sh)
	{
		while (sv->sh->tdlst_pipe)
		{
			token = zero_index_quotes(sv, n);
			if (!process_token(n, token))
				return ;
			if (n->i)
				execute_pipe(n, sv);
			token = next_pipe(sv);
		}
		next_semicolon(sv);
	}
	sv->sh = sv->sh_head;
	free(n->cmd);
	free(n);
}
