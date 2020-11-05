/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:14:13 by lhelper           #+#    #+#             */
/*   Updated: 2020/11/05 13:26:14 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_found(int i, t_norm *n, char **args)
{
	n->tmp = ft_strjoin("/", args[0]);
	(n->path)[i] = ft_strjoin_free_s1((n->path)[i], n->tmp);
	g_pid = fork();
	if (g_pid)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		waitpid(g_pid, &n->status, WUNTRACED);
		signal(SIGQUIT, handle_parent_signal);
		signal(SIGINT, handle_parent_signal);
		g_exit = status_return(n->status);
	}
	else
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		n->status = execve((n->path)[i], args, n->envp);
	}
	free(n->tmp);
	free_splitted(n);
	closedir(n->dir);
	free(n);
}

void	cmd_not_found(t_norm *n, char **args)
{
	if (n->path)
		free_splitted(n);
	free(n);
	write(0, PROM, ft_strlen(PROM));
	write(2, args[0], ft_strlen(args[0]));
	ft_putstr_fd(": command not found\n", 2);
	g_exit = 127;
}

void	init_envp(int *i, t_norm **n)
{
	*i = 0;
	*n = malloc(sizeof(t_norm));
	ft_alloc_check(n);
	(*n)->envp = list_to_env();
}

void	get_paths(t_norm *n)
{
	n->to_split = get_envar("PATH");
	n->path = ft_split(n->to_split, ':');
}

void	myclosedir(t_norm *n)
{
	if (n->dir)
		closedir(n->dir);
}
