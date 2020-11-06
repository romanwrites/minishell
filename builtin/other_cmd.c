/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 23:39:30 by lhelper           #+#    #+#             */
/*   Updated: 2020/11/06 15:14:26 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_err(int status, char *tmp, struct stat buffer)
{
	if (status == 0 && (buffer.st_mode & S_IXUSR) == 0)
	{
		write(0, PROM, ft_strlen(PROM));
		write(2, tmp, ft_strlen(tmp));
		ft_putstr_fd(": Permission denied\n", 2);
		g_exit = 126;
	}
	else if (status == 1)
	{
		write(0, PROM, ft_strlen(PROM));
		write(2, tmp, ft_strlen(tmp));
		ft_putstr_fd(": is a directory\n", 2);
		g_exit = 126;
	}
	else
	{
		write(0, PROM, ft_strlen(PROM));
		write(2, tmp, ft_strlen(tmp));
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit = 127;
	}
}

void	execute_slash(t_norm *n, char **args)
{
	struct stat		buffer;
	DIR				*dir;
	char			*tmp;
	int				status;

	tmp = args[0];
	args[0] = find_cmd(tmp);
	status = stat(tmp, &buffer);
	dir = opendir(tmp);
	if (dir)
	{
		closedir(dir);
		status = 1;
	}
	if (status == 0 && (buffer.st_mode & S_IXUSR) != 0)
		process_slash(status, tmp, args, n->envp);
	else
		handle_err(status, tmp, buffer);
	free_envp(n->envp);
	free(n);
	free(args[0]);
}

void	handle_cmd(char **args)
{
	t_norm	*n;
	int		i;

	init_envp(&i, &n);
	if (ft_strchr(args[0], '/'))
	{
		execute_slash(n, args);
		return ;
	}
	get_paths(n);
	while (n->path && n->path[i])
	{
		n->dir = opendir(n->path[i]);
		while (n->dir && (n->entry = readdir(n->dir)))
		{
			if (!ft_strcmp(args[0], n->entry->d_name))
			{
				command_found(i, n, args);
				return ;
			}
		}
		myclosedir(n);
		i++;
	}
	cmd_not_found(n, args);
}
