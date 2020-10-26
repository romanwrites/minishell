/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:30:21 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/26 17:13:14 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		process_cmd(t_mshell *sv)
{
	t_token *token;
	char **cmd;
	char *last_redir;
	int fd;
	int fds[2];
	int i;
	int x;
	int pid;
	int savestdout; 
	int savestdin; 
	savestdin = dup(0);
	savestdout = dup(1);
	int com = 0;
	cmd = (char **)malloc((sizeof(char *) * PATH_MAX));
	fd = -1;
	fds[0] = -1;
	fds[1] = -1;
	last_redir = NULL;
	while (sv->sh)
	{
		while (sv->sh->tdlst_pipe)
		{
			sv->sh->tdlst_pipe->token_head = sv->sh->tdlst_pipe->token;
			token = sv->sh->tdlst_pipe->token;
			open_quotes(&token);
			token = sv->sh->tdlst_pipe->token_head;
			i = 0;
			while (token)
			{
				if (((!ft_strcmp(token->content, ">") || !ft_strcmp(token->content, ">>") || !ft_strcmp(token->content, "<")) && token->is_diff && token->next && token->next->content && (ft_strcmp(token->next->content, ">") && ft_strcmp(token->next->content, ">>") && ft_strcmp(token->next->content, "<"))))
				{
					if (fd != -1)
						close(fd);
					fd = handle_redir(token->content, token->next->content);
					last_redir = token->content;
					if (fd == -1)
						return ;
					token = token->next;//QUESTIONABLE BUT DOESN'T REQUIRE IS_HANDLED
				}
				else if ((!ft_strcmp(token->content, ">") || !ft_strcmp(token->content, ">>") || !ft_strcmp(token->content, "<")) && token->is_diff && token->next && token->next->content && (!ft_strcmp(token->next->content, ">") || !ft_strcmp(token->next->content, ">>") || !ft_strcmp(token->next->content, "<")))
				{
					write(0, PROM, ft_strlen(PROM));
					write(1, "syntax error near unexpected token `", ft_strlen("syntax error near unexpected token `"));
					write(1, token->next->content, ft_strlen(token->next->content));
					write(1, "'\n", ft_strlen("'\n"));
					return ;
				}
				else
					cmd[i++] = token->content;
				//print_2d_array(cmd);
				token = token->next;
			}
			if (i)
			{
				cmd[i] = NULL;
				if (sv->sh->tdlst_pipe->next)
				{
					pipe(fds);
					pid = fork();
				   	if (pid == 0)
					{
						signal(SIGQUIT, SIG_DFL);
						signal(SIGINT, SIG_DFL);
						close(fds[0]);
						dup2(fds[1], 1);
						close(fds[1]);
						execute_command(cmd, last_redir, fd);
						exit((int)g_exit%256);//
					}
					else
					{
						signal(SIGQUIT, SIG_IGN);
						signal(SIGINT, SIG_IGN);
						wait(NULL);
						signal(SIGQUIT, handle_parent_signal);
						signal(SIGINT, handle_parent_signal);
						close(fds[1]);
						dup2(fds[0], 0);
						close(fds[0]);
					}
				}
				else
				{
					execute_command(cmd, last_redir, fd);
					dup2(savestdin, 0);
					dup2(savestdout, 1);
				}
			}
			token = sv->sh->tdlst_pipe->token_head;
			sv->sh->tdlst_pipe = sv->sh->tdlst_pipe->next;
		}
		sv->sh = sv->sh->next;
	}
}