/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:09:27 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/31 01:03:40 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void all_to_lower(char **cmd)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while(cmd[i])
	{
		while(cmd[i][x])
		{
			cmd[i][x] = ft_tolower(cmd[i][x]);
			x++;
		}
		i++;
		x = 0;
	}
}

void 	execute(char **cmd)
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
		if (!g_bp[0])
			ft_exit(cmd);
		return ;
	}
	else if (!(ft_strcmp(cmd[0], "cd")))
	{
		if (!g_bp[0])
			ft_cd(cmd[1]);
		return ;
	}
	else if (!(ft_strcmp(cmd[0], "unset")))
		ft_unset(cmd);
	else
	{
		all_to_lower(cmd);
		handle_cmd(cmd);
	}
}

int	handle_redir(char *is_redir, char *file)
{
	int fd;

	fd = -1;
	if (is_redir)
	{
		if(!ft_strcmp(is_redir, ">"))
			fd = open(file, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if(!ft_strcmp(is_redir, "<"))
			fd = open(file, O_RDONLY);
		else
			fd = open(file, O_APPEND | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	return (fd);
}

void 	execute_command(char **cmd, char *is_redir, int fdr, int fdl)
{
    int savestdout = dup(1);
    int savestdin = dup(0);
	
	//printf("fdr %d\t fdl %d\n", fdr, fdl);
	if (fdr != -2)
		dup2(fdr, 1);
	if (fdr != -2)
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
		/*
		if (filedes == -1)
		{
			if (!ft_strcmp(is_redir, "<"))
				dup2(fd, 0);
			else
				dup2(fd, 1);
			execute(cmd);//
			if (!ft_strcmp(is_redir, "<"))//
				dup2(savestdin, 0);//
			else//
				dup2(savestdout, 1);//
		}
		else
		{
			if (!ft_strcmp(is_redir, "<"))
			{
				dup2(fd, 0);
				dup2(filedes, 1);
			}
			else
			{
				dup2(fd, 1);
				dup2(filedes, 0);
			}
			execute(cmd);
			dup2(savestdin, 0);
			dup2(savestdout, 1);
			close(filedes);
		}
		close(fd);
		*/
}