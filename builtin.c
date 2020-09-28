/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:33:29 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/28 16:02:15 by lhelper          ###   ########.fr       */
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
		write(1, *env, ft_strlen(*env));
		write(1, "\n", 1);
		env++;
	}
}

void	freeEnv(char **envArray, int lines)
{
	while (lines >= 0)
	{
		free(envArray[lines]);
		lines--;
	}
	free(envArray);
}

char	**allocMemEnv(int lines, int maxLen)
{
	char	**envArray;
	int		i;

	i = 0;
	envArray = (char **)malloc(sizeof(char *) * lines);
	if (!envArray)
		return (envArray);
	while (i < lines)
	{
		envArray[i] = malloc(maxLen + 1);
		if (!(envArray[i]))
		{
			freeEnv(envArray, i);
			return(NULL);
		}
		i++;
	}
	return(envArray);
}

void	fillEnv(char **envArray)
{
	char	**env;
	
	env = g_envp;
	while((*env))
	{
		ft_strlcat((*envArray), (*env), ft_strlen(*env) + 1);
		envArray++;
		env++;
	}
}

void	sortEnv(char **envArray, int lines, int maxLen)
{
	char *tmp;
	int i;

	i = 0;
	while(lines > 1)
	{
		while  (i < lines - 1)
		{
			if (ft_strncmp(envArray[i], envArray[i + 1], maxLen) > 0)
			{
				tmp = envArray[i];
				envArray[i] = envArray[i + 1];
				envArray[i + 1] = tmp;
			}
			i++;
		}
		i = 0;
		lines--;
	}
}

void	printEnv(char **envArray)
{
	while (*envArray)
	{
		write(1, *envArray, ft_strlen(*envArray));
		write(1, "\n", 1);
		envArray++;
	}
}
/*
char	**reallocMemEnv(char **envArray, char *arg, int *lines)
{
	char	**ptrArray;

	(*lines)++;
	ptrArray = (char **)malloc(sizeof(char *) * (*lines));
	if (!ptrArray)
		return (ptrArray);
	ft_memcpy(ptrArray, envArray, sizeof(char *) * (*lines));
	ft_strcpy(ptrArray[(*lines) - 2], arg);
	//freeEnv(envArray, *lines - 2);
	return(ptrArray);
}
*/

void	countLines(int *lines, int *maxLen, char *arg)
{
	char	**env;

	env = g_envp;
	while((*env))
	{
		*maxLen = (*maxLen > ft_strlen(*env)) ? *maxLen : ft_strlen(*env);
		env++;
		(*lines)++;
	}
	if (arg)
	{
		g_envp = realloc(g_envp, (*lines) + 1);
		g_envp[*lines] = malloc(*maxLen);
		ft_strcpy(g_envp[*lines], arg);
		printf("\n\n%s\n", arg);
		printf("%s\n\n", g_envp[*lines]);
	}
}

void	ft_export(char *arg) //add var
{
	char	**envArray;
	int		lines;
	int		maxLen;

	lines = 0;
	maxLen = 0;
	envArray = NULL;
	
	countLines(&lines, &maxLen, arg);
	envArray = allocMemEnv(lines, maxLen);
	if (envArray == NULL)
		return ;
	fillEnv(envArray);
	sortEnv(envArray, lines, maxLen);
	/*
	if (arg)
	{
		envArray = reallocMemEnv(envArray, arg, &lines);
		if (envArray == NULL)
			return ;
	}
	*/
	printEnv(envArray);
	freeEnv(envArray, lines);
}

void	ft_unset(char *arg) //revome var
{
	if (!arg)
	{
		write(1, "unset: not enough arguments", ft_strlen("unset: not enough arguments"));
		write(1, "\n", 1);
	}
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
	//ft_cd(argv[1]);
	ft_exit(0);
	printf("ur exit doesnt work");
    return 0;
}