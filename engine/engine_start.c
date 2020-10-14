/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:39:20 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/14 21:19:37 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*g_env;
char	*input;
pid_t	pid;

void	state_bzero(t_parse *state)
{
	state->is_double_quote_open = 0;
	state->is_single_quote_open = 0;
	state->backslash = 0;
	state->backslash_time = 0;
}

void	init(t_mshell	*sv)
{
	sv->content = NULL;
	sv->i = 0;
	sv->state = (t_parse *)malloc(sizeof(t_parse) * 1); // free after parse
	ft_alloc_check(sv->state);
	state_bzero(sv->state);
}

void ignore()
{
	write(0, "\b\b  \b\b", 6);
}

void new_line()
{
	write(0, "\b\b  \b\b", 6);
	write(0, "\nzaebash-3.2$ ", ft_strlen("\nzaebash-3.2$ "));
}

//////////
char **list_to_env()
{
	t_list *list;
	char **envp;
	char *tmp;
	char *str;
	int i;
	int len;

	i = 0;
	list = g_env;
	while(list)
	{
		i++;
		list = list->next;
	}
	list = g_env;
	envp = (char **)malloc(sizeof(char**) * i);
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
	}
	envp[len] = NULL;
}

void	handle_cmd(char *cmd, char **args)
{
	char *to_split;
	char *tmp;
	char **path;
	char **envp;
	DIR *dir;
	struct dirent *entry;

	to_split = get_envar("PATH");
	path = ft_split(to_split, ':');
	envp = list_to_env();
	tmp = cmd;
	cmd = ft_strjoin("/", cmd);
	free(tmp);
	while(path)
	{
		dir = opendir(*path);
		while(entry = readdir(dir))
		{
			if(!ft_strcmp(cmd, entry->d_name));
			{
				tmp = ft_strjoin(path, cmd);
				execve(tmp, args, envp);
				free(tmp);
				closedir(dir);
				return ;
			}
		}
		closedir(dir);
		path++;
	}
	//command not found0
}

void ft_test(char *str)
{
	if (*str == '\0')
		return ;
	char **cmd = ft_split(str, ' ');
	if (!(strcmp(cmd[0], "export")))
		ft_export(cmd[1]);
	else if (!(strcmp(cmd[0], "env")))
		ft_env();
	else if (!(strcmp(cmd[0], "pwd")))
		ft_pwd();
	else if (!(strcmp(cmd[0], "echo")))
	{
		if (cmd[1])
			ft_echo(cmd[1], 0);
	}
	else if (!(strcmp(cmd[0], "exit")))
		ft_exit(0);
	else if (!(strcmp(cmd[0], "cd")))
	{
		if (cmd[1])
			ft_cd(cmd[1]);
	}
	else if (!(strcmp(cmd[0], "unset")))
		ft_unset(cmd[1]);
	else if (!(strcmp(cmd[0], "ls")))
		handle_cmd("ls", NULL);
}
//////////

int     main(int ac, char **av, char **envp)
{
	t_mshell	*sv;

	(void)ac;
	(void)av;

	signal(SIGQUIT, ignore);
	signal(SIGINT, new_line);
	g_env = env_to_list(envp);
	sv = (t_mshell *)malloc(sizeof(t_mshell));
	ft_alloc_check(sv);
	init(sv);
	//sv->envp_mshell = (void *)envp;

	int fd = open("parse_tests.txt", O_RDONLY);
	write(0, "zaebash-3.2$ ", ft_strlen("zaebash-3.2$ "));
	while (get_next_line(0, &sv->content))
	{
		ft_test(sv->content);//
		write(0, "zaebash-3.2$ ", ft_strlen("zaebash-3.2$ "));
		//ft_alloc_check(sv->content);
		//parse_input(sv);
		//t_dlst *tmp = sv->dlst_head
		//char **ptr = (char **)(sv->dlst_head)->content;
		//tmp = tmp->next;
		//print_2d_array(ptr);
		free(sv->content);
		sv->content = NULL;
	}
	if (*(sv->content) == '\0')
		write(0, "exit\n", ft_strlen("exit\n"));
	return (0);
	//parse_input(sv);
	//if (sv->content)
	//   free(sv->content);
	//sv->content = NULL;
	//free(sv);
	//sv = NULL;
	//sleep(30);
}