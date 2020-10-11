/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:39:20 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/11 20:28:22 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

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

void new_line()
{
	write(0, "\b\b  \b\b", 6);
	write(0, "\nzaebash-3.2$ ", ft_strlen("\nzaebash-3.2$ "));
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
}

int     main(int ac, char **av, char **envp)
{
	t_mshell	*sv;

	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);//write (1, "\b", 1);
	signal(SIGINT, new_line);

	g_env = envp;
	sv = (t_mshell *)malloc(sizeof(t_mshell));
	ft_alloc_check(sv);
	init(sv);
	sv->envp_mshell = (void *)envp;

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