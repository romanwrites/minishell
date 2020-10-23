/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 23:39:30 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/23 21:01:51 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "../includes/minishell.h"

char **list_to_env()
{
	t_list *list;
	char **envp;
	char *tmp;
	char *str;
	int i;
	int len;

	i = 0;
	len = 0;
	list = g_env;
	while(list)
	{
		i++;
		list = list->next;
	}
	list = g_env;
	envp = (char **)malloc(sizeof(char*) * i + 1);
	while(len < i)
	{
		envp[len] = (char *)malloc(PATH_MAX);
		str = ft_strjoin(((t_envar *)(list->content))->key, "=");
		tmp = str;
		str = ft_strjoin(str, ((t_envar *)(list->content))->value);
		free(tmp);
		envp[len] = ft_memcpy(envp[len], str, ft_strlen(str));
		free(str);
		len++;
		list = list->next;
	}
	envp[len] = NULL;
	return(envp);
}

char	*find_cmd(char *path)
{
	int len;
	int i;
	char *cmd;

	len = ft_strlen(path);
	i = len;
	while(len > 0 && path[len] != '/')
		len--;
	i = i - len;
	cmd = malloc(i);
	if (cmd)
		ft_memcpy(cmd, &path[++len], i);
	return(cmd);
}

void	handle_cmd(char **args)
{
	char *to_split;
	char *tmp;
	char **path;
	char **envp;
	DIR *dir;
	struct dirent *entry;
	int i;
	int x;

	i = 0;
	x = 0;
	envp = list_to_env();
	if (args[0][0] == '/')
	{
		tmp = args[0];
		args[0] = find_cmd(tmp);
		g_pid = fork();
		if (g_pid)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, SIG_IGN);
			wait(NULL);
			signal(SIGQUIT, handle_parent_signal);
			signal(SIGINT, handle_parent_signal);
		}
		else
		{
			signal(SIGQUIT, handle_child_signal);
			signal(SIGINT, handle_child_signal);
			execve(tmp, args, envp);
		}
		free(tmp);
		return ;
	}
	to_split = get_envar("PATH");
	path = ft_split(to_split, ':');
	while(path && path[i])
	{
		dir = opendir(path[i]);
		while(dir && (entry = readdir(dir)))
		{
			if(!ft_strcmp(args[0], entry->d_name))
			{
				tmp = ft_strjoin("/", args[0]);
				path[i] = ft_strjoin_free_s1(path[i], tmp);
				g_pid = fork();
				if (g_pid)
				{
					signal(SIGQUIT, SIG_IGN);
					signal(SIGINT, SIG_IGN);
					wait(NULL);
					signal(SIGQUIT, handle_parent_signal);
					signal(SIGINT, handle_parent_signal);
				}
				else
				{
					signal(SIGQUIT, handle_child_signal);
					signal(SIGINT, handle_child_signal);
					execve(path[i], args, envp);
				}
				free(tmp);
				free(to_split);
				while (path[x])
				{
					free(path[x]);
					x++;
				}
				free(path);
				closedir(dir);
				return ;
			}
		}
		if (dir)
			closedir(dir);
		i++;
	}
	if (path)
	{
		while (path[x])
		{
			free(path[x]);
			x++;
		}
		free(path);
		free(to_split);
	}
	write(1, PROM, ft_strlen(PROM));//why zero??????
	write(1, args[0], ft_strlen(args[0]));
	write(1, ": No such file or directory\n", ft_strlen(": No such file or directory\n"));
}