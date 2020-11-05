/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:30:21 by lhelper           #+#    #+#             */
/*   Updated: 2020/11/05 16:43:51 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool	g_bp;

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

void		timer(void)
{
	if (g_exit && !g_timer)
		g_timer = 2;
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

void		process_cmd(t_mshell *sv)
{
	t_token *token;
	t_norma	*n;

	n = malloc(sizeof(t_norma));
	init_vars(n);
	while (sv->sh)
	{
		timer();
		while (sv->sh->tdlst_pipe)
		{
			token = zero_index_quotes(sv, n);
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
						return ;
					}
					token = token->next;
				}
				else
					add_token(n, token);
				token = token->next;
			}
			if (n->i)
				execute_pipe(n, sv);
			token = next_pipe(sv);
		}
		sv->sh->tdlst_pipe = sv->sh->tdlst_pipe_head;
		sv->sh = sv->sh->next;
	}
	sv->sh = sv->sh_head;
	free(n);
}
