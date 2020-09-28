/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:33:29 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/28 19:59:51 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char		**g_envp;

#include "includes/minishell.h"

void	ft_echo(char *str, int flag_n) //"" '' \n \t \0!!!!!!!!!!!!!!!!!!!!!!!!!
{
	write(1, str, ft_strlen(str));
	if (!flag_n)
		write(1, "\n", 1);
}

void	ft_exit(int exit_code)
{
	exit(exit_code);
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
	dir = opendir(str);
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
		write(1, *env, ft_strlen(*env));
		write(1, "\n", 1);
		env++;
	}
}

void	free_env(char **env_array, int lines)
{
	while (lines >= 0)
	{
		free(env_array[lines]);
		lines--;
	}
	free(env_array);
}

char	**alloc_mem_env(int lines, int max_len, char *arg)
{
	char	**env_array;
	int		i;

	i = 0;

	env_array = (char **)malloc(sizeof(char *) * lines + 1);
	if (!env_array)
		return (env_array);
	while (i < lines)
	{
		env_array[i] = malloc(max_len + 1);
		if (!(env_array[i]))
		{
			free_env(env_array, i);
			return(NULL);
		}
		i++;
	}
	return(env_array);
}

void	fill_env(char **env_array, char *arg)
{
	char	**env;
	
	env = g_envp;
	while((*env))
	{
		ft_strlcat((*env_array), (*env), ft_strlen(*env) + 1);
		env_array++;
		env++;
	}
	if (arg)
	{
		ft_strlcat((*env_array), arg, ft_strlen(arg) + 1);
		env_array++;
	}
	*env_array = NULL;
}

void	sort_env(char **env_array, int lines, int max_len)
{
	char *tmp;
	int i;

	i = 0;
	while(lines > 1)
	{
		while  (i < lines - 1)
		{
			if (ft_strncmp(env_array[i], env_array[i + 1], max_len) > 0)
			{
				tmp = env_array[i];
				env_array[i] = env_array[i + 1];
				env_array[i + 1] = tmp;
			}
			i++;
		}
		i = 0;
		lines--;
	}
}

void	print_env(char **env_array)
{
	while (*env_array)
	{
		write(1, *env_array, ft_strlen(*env_array));
		write(1, "\n", 1);
		env_array++;
	}
}

void	count_lines(int *lines, int *max_len, char *arg)
{
	char	**env;

	env = g_envp;
	while((*env))
	{
		*max_len = (*max_len > ft_strlen(*env)) ? *max_len : ft_strlen(*env);
		env++;
		(*lines)++;
	}
	/*
	if (arg)
	{
		g_envp = realloc(g_envp, (*lines) + 1);
		g_envp[*lines] = malloc(*max_len);
		ft_strcpy(g_envp[*lines], arg);
		printf("\n\n%s\n", arg);
		printf("%s\n\n", g_envp[*lines]);
	}
	*/
	if (arg)
		(*lines)++;
}

void	ft_export(char *arg) //handle ='' & many varS using ft_split(' ')
{
	char	**env_array;
	int		lines;
	int		max_len;

	lines = 0;
	max_len = 0;
	env_array = NULL;
	
	count_lines(&lines, &max_len, arg);
	env_array = alloc_mem_env(lines, max_len, arg);
	if (env_array == NULL)
		return ;
	fill_env(env_array, arg);
	sort_env(env_array, lines, max_len);
	print_env(env_array);
	free_env(env_array, lines);//place at EXIT
}

void	ft_unset(char *arg) //revome varS
{
	if (!arg)
	{
		write(1, "unset: not enough arguments", ft_strlen("unset: not enough arguments"));
		write(1, "\n", 1);
	}
}


///////////////////////////////////////////////////////////////////////////////
void	echo_assert_test()
{
	printf("_________BACKSLASH________\n");
	ft_echo("", 0);
	ft_echo("su\p", 0); //su/p warning: unknown escape sequence '\p' [-Wunknown-escape-sequence]
	ft_echo("su\tp", 0);
	ft_echo("su\np", 0);
	ft_echo("su\0p", 0); //sup
	ft_echo("sup\n", 0);
}

int main(int argc, char **argv, char **envp)
{
	g_envp = envp;
	echo_assert_test();
	//ft_pwd();
	/*
	if (argv[1][0] == 'e' && argv[1][1] == 'n' && argv[1][2] == 'v' && argv[1][3] == '\0')
	{
		ft_env();
		return 0;
	}
	if (!(strcmp(argv[1], "unset")))
	{
		ft_unset(0);
		return 0;
	}
	if (!(strcmp(argv[1], "export")))
	{
		if (!(argv[3]))
			ft_export(0);
		else
			ft_export(argv[3]);
		return 0;
	}
	*/
	ft_cd(argv[1]);
	ft_exit(0);
	printf("ur exit doesnt work");
    return 0;
}