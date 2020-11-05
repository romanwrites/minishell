/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 17:07:57 by lhelper           #+#    #+#             */
/*   Updated: 2020/11/05 17:15:17 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*zero_index_quotes(t_mshell *sv, t_norma *n)
{
	t_token *token;

	sv->sh->tdlst_pipe->token_head = sv->sh->tdlst_pipe->token;
	token = sv->sh->tdlst_pipe->token;
	open_quotes(token);
	token = sv->sh->tdlst_pipe->token;
	n->i = 0;
	return (token);
}

void		left_or_right(t_norma *n, t_token *token)
{
	if (token->content[0] == '>')
	{
		if (n->fdr != -2)
			close(n->fdr);
		n->fdr = handle_redir(token->content, token->next->content);
	}
	else if (token->content[0] == '<')
	{
		if (n->fdl != -2)
			close(n->fdl);
		n->fdl = handle_redir(token->content, token->next->content);
	}
}

void		preexecute_pipe(t_norma *n)
{
	fill_before_pipe(n);
	pipe(n->fds);
	n->pid = fork();
}

void		fill_before_pipe(t_norma *n)
{
	if (n->cmd && n->cmd[0])
		g_bp = 1;
	else
		g_bp = 0;
}

void		print_no_file_dir(char *str)
{
	ft_putstr_fd(PROM, 0);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
