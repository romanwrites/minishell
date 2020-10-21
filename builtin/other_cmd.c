/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 23:39:30 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/17 16:12:52 by lhelper          ###   ########.fr       */
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

void	handle_cmd(char *cmd)
{
	char **args;
	char *to_split;
	char *tmp;
	char **path;
	char **envp;
	DIR *dir;
	struct dirent *entry;
	int i = 0;
	int x = 0;

	args = ft_split(cmd, ' ');
	to_split = get_envar("PATH");
	path = ft_split(to_split, ':');
	envp = list_to_env();
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
					wait(NULL);
				else
					execve(path[i], args, envp);
				free(tmp);
				free(to_split);
				while (args[x])
				{
					free(args[x]);
					x++;
				}
				free(args);//in a loop
				x = 0;
				while (path[x])
				{
					free(path[x]);
					x++;
				}
				free(path);//in a loop
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
		free(path);//in a loop
		free(to_split);
	}
	x = 0;
	write(1, "minishell: ", ft_strlen("minishell: "));
	write(1, args[0], ft_strlen(args[0]));
	write(1, ": No such file or directory\n", ft_strlen(": No such file or directory\n"));
	if (args)
	{
		while (args[x])
		{
			free(args[x]);
			x++;
		}
		free(args);//in a loop
	}
}