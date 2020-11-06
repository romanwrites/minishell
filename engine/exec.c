/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:09:27 by mkristie          #+#    #+#             */
/*   Updated: 2020/11/06 14:15:32 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	all_to_lower(char **cmd)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (cmd[i])
	{
		while (cmd[i][x])
		{
			cmd[i][x] = ft_tolower(cmd[i][x]);
			x++;
		}
		i++;
		x = 0;
	}
}

void	handle_other(char **cmd)
{
	all_to_lower(cmd);
	handle_cmd(cmd);
}

void	execute(char **cmd)
{
	if (!(ft_strcmp(cmd[0], "export")))
		ft_export(cmd);
	else if (!(ft_strcmp(cmd[0], "env")))
		ft_env();
	else if (!(ft_strcmp(cmd[0], "pwd")))
		ft_pwd();
	else if (!(ft_strcmp(cmd[0], "echo")))
		ft_echo(cmd);
	else if (!(ft_strcmp(cmd[0], "exit")))
	{
		if (!g_bp)
			ft_exit(cmd);
		return ;
	}
	else if (!(ft_strcmp(cmd[0], "cd")))
	{
		if (!g_bp)
			ft_cd(cmd[1]);
		return ;
	}
	else if (!(ft_strcmp(cmd[0], "unset")))
		ft_unset(cmd);
	else
		handle_other(cmd);
}

int		handle_redir(char *is_redir, char *file)
{
	int fd;

	fd = -1;
	if (is_redir)
	{
		if (!ft_strcmp(is_redir, ">"))
			fd = open(file, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | \
			S_IWUSR | S_IRGRP | S_IROTH);
		else if (!ft_strcmp(is_redir, "<"))
			fd = open(file, O_RDONLY);
		else
			fd = open(file, O_APPEND | O_WRONLY | O_CREAT, S_IRUSR | \
			S_IWUSR | S_IRGRP | S_IROTH);
	}
	return (fd);
}

void	execute_command(char **cmd, int fdr, int fdl)
{
	int	savestdout;
	int	savestdin;

	savestdout = dup(1);
	savestdin = dup(0);
	if (fdr != -2)
		dup2(fdr, 1);
	if (fdl != -2)
		dup2(fdl, 0);
	execute(cmd);
	if (fdr != -2)
	{
		close(fdr);
		fdr = -2;
		dup2(savestdout, 1);
	}
	if (fdl != -2)
	{
		close(fdl);
		fdl = -2;
		dup2(savestdin, 0);
	}
}
