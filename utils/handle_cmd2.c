/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:14:15 by lhelper           #+#    #+#             */
/*   Updated: 2020/11/05 13:35:05 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		list_size(void)
{
	t_list	*list;
	int		i;

	i = 0;
	list = g_env;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

char	**list_to_env(void)
{
	t_list	*list;
	char	**envp;
	char	*tmp;
	char	*str;
	int		i[2];

	i[0] = 0;
	i[1] = list_size();
	list = g_env;
	envp = (char **)malloc(sizeof(char*) * i[1] + 1);
	while (i[0] < i[1])
	{
		envp[i[0]] = (char *)malloc(PATH_MAX);
		str = ft_strjoin(((t_envar *)(list->content))->key, "=");
		tmp = str;
		str = ft_strjoin(str, ((t_envar *)(list->content))->value);
		free(tmp);
		envp[i[0]] = ft_memcpy(envp[i[0]], str, ft_strlen(str));
		free(str);
		i[0]++;
		list = list->next;
	}
	envp[i[0]] = NULL;
	return (envp);
}

char	*find_cmd(char *path)
{
	int		len;
	int		i;
	char	*cmd;

	len = ft_strlen(path);
	i = len;
	while (len > 0 && path[len] != '/')
		len--;
	i = i - len;
	cmd = malloc(i);
	if (cmd)
		ft_memcpy(cmd, &path[++len], i);
	return (cmd);
}

void	process_slash(int status, char *tmp, char **args, char **envp)
{
	g_pid = fork();
	if (g_pid)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		waitpid(g_pid, &status, WUNTRACED);
		signal(SIGQUIT, handle_parent_signal);
		signal(SIGINT, handle_parent_signal);
		g_exit = status_return(status);
	}
	else
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		status = execve(tmp, args, envp);
	}
}

void	free_splitted(t_norm *n)
{
	int x;

	x = 0;
	while ((n->path)[x])
	{
		free((n->path)[x]);
		x++;
	}
	free(n->path);
	free(n->to_split);
}
