/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:30:21 by lhelper           #+#    #+#             */
/*   Updated: 2020/11/03 18:57:40 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_bp;

void	fill_before_pipe(char **cmd, int i)
{
	int x;

	x = 0;
	while(g_bp[x])
	{
		free(g_bp[x]);
		x++;
	}
	x = 0;
	while (x < i)
	{
		g_bp[x] = ft_strdup(cmd[x]);
		x++;
	}
	g_bp[x] = NULL;
}

void	print_no_file_dir(char *str)
{
	ft_putstr_fd(PROM, 0);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	process_cmd(t_mshell *sv)
{
	t_token *token;
	char **cmd;
	char *last_redir;
	int fd;
	int filedes;
	int fds[2];
	int i;
	int x;
	int status;
	int pid;
	int savestdout; 
	int savestdin; 
	//int timer;
	savestdin = dup(0);
	savestdout = dup(1);
	cmd = (char **)malloc((sizeof(char *) * PATH_MAX));
	g_bp = (char **)malloc((sizeof(char *) * PATH_MAX));
	int fdl = -2;
	int fdr = -2;
	fd = -1;
	filedes = -1;
	fds[0] = -1;
	fds[1] = -1;
	//timer = 0;
	last_redir = NULL;
	g_bp[0] = NULL;
	while (sv->sh)
	{
		if (g_exit && !g_timer)
			g_timer = 2;
		if (g_timer)
		{
			g_timer--;
			if (!g_timer)
				g_exit = 0;
		}
		while (sv->sh->tdlst_pipe)
		{
			sv->sh->tdlst_pipe->token_head = sv->sh->tdlst_pipe->token;
			token = sv->sh->tdlst_pipe->token;
			open_quotes(token);
			token = sv->sh->tdlst_pipe->token;
			i = 0;
			while (token)
			{
				if ((check_redirs_only(token->content) && token->is_diff && token->next && (!check_redirs_only(token->next->content))))
				{
					if (token->content[0] == '>')
					{
						if (fdr != -2)
							close(fdr);
						fdr = handle_redir(token->content, token->next->content);
					}
					else if (token->content[0] == '<')
					{
						if (fdl != -2)
							close(fdl);
						fdl = handle_redir(token->content, token->next->content);
					}
					last_redir = token->content;
					if (fdr == -1 || fdl == -1)
					{
						print_no_file_dir(token->next->content);
						return ;
					}
					token->tick = 1;
					token->next->tick = 1;
					token = token->next;
				}
				else
				{
					cmd[i++] = token->content;
					cmd[i] = NULL;
					//print_2d_array(cmd);
				}
				token = token->next;
			}
			if (i)
			{
				if (sv->sh->tdlst_pipe->next)
				{
					fill_before_pipe(cmd, i);
					pipe(fds);
					pid = fork();
				   	if (pid == 0)
					{
						signal(SIGQUIT, SIG_DFL);
						signal(SIGINT, SIG_DFL);
						close(fds[0]);
						dup2(fds[1], 1);
						close(fds[1]);
						execute_command(cmd, last_redir, fdr, fdl);
						exit((int)g_exit%256);//
					}
					else
					{
						signal(SIGQUIT, SIG_IGN);
						signal(SIGINT, SIG_IGN);
						wait(NULL);
						//waitpid(g_pid, &status, WUNTRACED);
						signal(SIGQUIT, handle_parent_signal);
						signal(SIGINT, handle_parent_signal);
						//g_exit = status_return(status);
						close(fds[1]);
						dup2(fds[0], 0);
						close(fds[0]);
						fdr = -2;
						fdl = -2;
					}
				}
				else
				{
					execute_command(cmd, last_redir, fdr, fdl);
					dup2(savestdin, 0);
					dup2(savestdout, 1);
				}
			}
			token = sv->sh->tdlst_pipe->token_head;
			sv->sh->tdlst_pipe = sv->sh->tdlst_pipe->next;
		}
		sv->sh->tdlst_pipe = sv->sh->tdlst_pipe_head;
		sv->sh = sv->sh->next;
	}
	sv->sh = sv->sh_head;
}