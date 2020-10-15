/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 23:39:30 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/16 00:28:48 by lhelper          ###   ########.fr       */
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

void	handle_cmd(char *cmd, char **args)
{
	char *to_split;
	char *tmp;
	char **path;
	char **envp;
	DIR *dir;
	struct dirent *entry;

	args = (char **)malloc(sizeof(char *) * 4);
	args[0] = ft_strdup(cmd);
	args[1] = ft_strdup("-e");
	args[2] = ft_strdup("cmd.txt");
	args[3] = NULL;
	to_split = get_envar("PATH");
	path = ft_split(to_split, ':');
	envp = list_to_env();
	int i = 0;
	while(path)
	{
		dir = opendir(*path);
		while((entry = readdir(dir)))
		{
			if(!ft_strcmp(cmd, entry->d_name))
			{
				cmd = ft_strjoin("/", cmd);
				tmp = ft_strjoin(*path, cmd);
				g_pid = fork();
				g_pid = wait(NULL);
				if (!g_pid)
				{
					execve(tmp, args, envp);
				}
				free(tmp);
				free(cmd);
				free(args[0]);
				free(args[1]);
				free(args[2]);
				free(args);
				closedir(dir);
				return ;
			}
		}
		closedir(dir);
		path++;
	}
	free(cmd);
	free(args[0]);
	free(args[1]);
	free(args[2]);
	free(args);
	write(1, "minishell: ", ft_strlen("minishell: "));
	write(1, cmd, ft_strlen(cmd));
	write(1, ": command not found\n", ft_strlen(": command not found\n"));
}