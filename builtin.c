/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:33:29 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/25 18:45:05 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char		**g_envp;

#include "minishell.h"

void	ft_echo(char *str, int flag_n) //"" '' !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
	write(1, str, ft_strlen(str));
	if (!flag_n)
		write(1, "\n", 1);
}

void	ft_exit(int exitCode)
{
	exit(exitCode);
}

void	ft_pwd()
{
	char path[PATH_MAX];

	getcwd(path, PATH_MAX);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
}

void	ft_cd(char *str)
{
	DIR *dir;
	struct dirent *entry;
	
	dir = NULL;
	printf("%p\n", dir);
	dir = opendir(str);
	printf("%p\n", dir);
	if (!dir)
	{
		write(1, "cd: ", ft_strlen("cd: "));
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, ": ", ft_strlen(": "));
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		return ;
	}
	closedir(dir);
	ft_pwd();//
	chdir(str);
	ft_pwd();//
}

void	ft_env()
{
	char **env;

	env = g_envp;
	while((*env))
	{
		printf("%s\n", *env);
		env++;
	}
}

void	ft_export(flag_arg)
{
	if (!flag_arg)
		ft_env();//???????????????????????????????????????????????????????????
}

void	ft_unset(flag_arg)
{
	if (!flag_arg)
		write(1, "unset: not enough arguments", ft_strlen("unset: not enough arguments"));
}


///////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv, char **envp)
{
	g_envp = envp;
    ft_echo(argv[1], atoi(argv[2]));
	//ft_pwd();
	if (argv[1][0] == 'e' && argv[1][1] == 'n' && argv[1][2] == 'v' && argv[1][3] == '\0')
	{
		ft_env();
		return 0;
	}
	ft_cd(argv[1]);
	ft_exit(0);
	printf("ur exit doesnt work");
    return 0;
}