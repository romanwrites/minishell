/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:30:21 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/22 16:35:44 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		process_cmd()
{
	t_token *token;
	char **cmd;
	char *last_redir;
	int fd;
	int fds[2];
	int i;
	int x;
	int pid;
	int after_pipe;
	int savestdout; 
	int savestdin; 
	savestdin = dup(0);
	savestdout = dup(1);
	int com = 0;
	cmd = (char **)malloc((sizeof(char *) * PATH_MAX));
	i = 0;
	fd = -1;
	after_pipe = 0;
	last_redir = NULL;
	while (g_sv->sh)
	{
		while (g_sv->sh->tdlst_pipe)
		{
			g_sv->sh->tdlst_pipe->token_head = g_sv->sh->tdlst_pipe->token;
			while ((token = g_sv->sh->tdlst_pipe->token))
			{
				open_quotes(&token);
				//if (token->is_handled)
				//	continue;
				if (((!ft_strcmp(token->content, ">") || !ft_strcmp(token->content, ">>") || !ft_strcmp(token->content, "<")) && token->is_diff && token->next && token->next->content && (ft_strcmp(token->next->content, ">") && ft_strcmp(token->next->content, ">>") && ft_strcmp(token->next->content, "<"))))
				{
					//cmd[i] = NULL;
					if (fd != -1)
						close(fd);
					fd = handle_redir(token->content, token->next->content);
					last_redir = token->content;
					if (fd == -1)
						return ;
					//token->next->is_handled = 1;
					
					//execute_command(cmd, token->content, token->next->content);
					g_sv->sh->tdlst_pipe->token = g_sv->sh->tdlst_pipe->token->next;//QUESTIONABLE BUT DOESN'T REQUIRE IS_HANDLED
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
				g_sv->sh->tdlst_pipe->token = g_sv->sh->tdlst_pipe->token->next;
			}
						//execve("/bin/cat", cat, envp);
			//в родительском не будет execve, 
			//просто будут меняться дескрипторы, эта функция должна вызываться в 
			//цикле и на следующей иттерации выполнять execve для второй части пайпа, 
			//но нужны два условия чтобы вначале не читать и в конце не менять дескрипторы? 
			//вроде так, удачи, Илюха из будущего
			if (i)
			{
				cmd[i] = NULL;
				i = 0;
				//execute_command(cmd, last_redir, fd);
				if (g_sv->sh->tdlst_pipe->next)
				{
					pipe(fds);
					pid = fork();
					if (pid == 0)
					{
						//if(!after_pipe)
						//{
							close(fds[0]);
							dup2(fds[1], 1);
							close(fds[1]);
							after_pipe = 1;
							execute_command(cmd, last_redir, fd);
						//}
						//else
						//	after_pipe = 0;
						exit(0);
					}
					else
					{
						wait(NULL);
						//if(!after_pipe)
						//{
							close(fds[1]);
							dup2(fds[0], 0);
							close(fds[0]);
							after_pipe = 1;
						//}
						//else
						//	after_pipe = 0;
					}
				}
				else
				{
					execute_command(cmd, last_redir, fd);
					dup2(savestdin, 0);
					dup2(savestdout, 1);
				}
			}
			token = g_sv->sh->tdlst_pipe->token_head;
			//print_token_list(token);
			//printf("semi: %d, pipe: %d, tok: %d\n", semi, pipe, ++tok);
			g_sv->sh->tdlst_pipe = g_sv->sh->tdlst_pipe->next;
		}
		g_sv->sh = g_sv->sh->next;
	}
}