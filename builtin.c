/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:33:29 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/28 12:59:47 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char		**g_envp;

#include "includes/minishell.h"

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
		write(1, *env, ft_strlen(*env));
		write(1, "\n", 1);
		env++;
	}
}

char	**allocMemEnv(int *lines, int *maxLen)
{
	char	**env;
	char	**envArray;
	int		linesCopy;

	envArray = NULL;
	env = g_envp;
	while((*env))
	{
		*maxLen = (*maxLen > ft_strlen(*env)) ? *maxLen : ft_strlen(*env);
		env++;
		(*lines)++;
	}
	envArray = (char **)malloc(sizeof(char *) * (*lines));
	linesCopy = *lines;
	while (linesCopy-- >= 0)
		envArray[linesCopy] = malloc(*maxLen + 1);
	//printf("maxLen=%d\n", *maxLen);
	//printf("Lines=%d\n", lines);
	//printf("malloced=%d\n", *maxLen * lines + lines);
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

void	freeEnv(char **envArray)
{
	
}

void	ft_export(flag_arg)
{
	char **envArray;
	int		lines;
	int		maxLen;

	lines = 0;
	maxLen = 0;
	envArray = NULL;
	if (!flag_arg)
	{
		envArray = allocMemEnv(&lines, &maxLen);
		if (envArray == NULL)
			return ;//??????????????????????????????????????????????????should I check every string?
		fillEnv(envArray);
		sortEnv(envArray, lines, maxLen);
		printEnv(envArray);
		freeEnv(envArray);
	}
}

void	ft_unset(flag_arg)
{
	if (!flag_arg)
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
		ft_export(0);
		return 0;
	}
	ft_cd(argv[1]);
	ft_exit(0);
	printf("ur exit doesnt work");
    return 0;
}

/*
USER=lhelper
PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:~/.dotnet/tools:/Library/Frameworks/Mono.framework/Versions/Current/Commands:/Applications/Visual Studio Code.app/Contents/Resources/app/bin:/Applications/Visual Studio Code.app/Contents/Resources/app/bin
LOGNAME=ilya
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.7HmaIICWLH/Listeners
HOME=/Users/ilya
SHELL=/bin/zsh
__CF_USER_TEXT_ENCODING=0x1F5:0x0:0x2
TMPDIR=/var/folders/q3/xj33tmqd7fv55fb23d4gc_kh0000gn/T/
XPC_SERVICE_NAME=0
XPC_FLAGS=0x0
ORIGINAL_XDG_CURRENT_DESKTOP=undefined
TERM_PROGRAM=vscode
TERM=xterm-256color
TERM_PROGRAM_VERSION=1.49.1
TERM_SESSION_ID=w0t0p0:A1A81A64-C9BD-4538-9EAF-100F85A7C57D
MAIL=marvin@42.fr
PWD=/Users/ilya/Desktop/school21/minishell
ITERM_PROFILE=Default
SHLVL=1
COLORFGBG=7;0
LC_TERMINAL_VERSION=3.3.9
ITERM_SESSION_ID=w0t0p0:A1A81A64-C9BD-4538-9EAF-100F85A7C57D
LC_CTYPE=UTF-8
LC_TERMINAL=iTerm2
COLORTERM=truecolor
APPLICATION_INSIGHTS_NO_DIAGNOSTIC_CHANNEL=true
OLDPWD=/Users/ilya/Desktop/school21/minishell
LANG=en_GB.UTF-8
VSCODE_GIT_IPC_HANDLE=/var/folders/q3/xj33tmqd7fv55fb23d4gc_kh0000gn/T/vscode-git-8dc7a77b2d.sock
GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh
VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Renderer).app/Contents/MacOS/Code Helper (Renderer)
VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js
_=/usr/bin/env
*/

/*
USER=lhelper
PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:~/.dotnet/tools:/Library/Frameworks/Mono.framework/Versions/Current/Commands:/Applications/Visual Studio Code.app/Contents/Resources/app/bin:/Applications/Visual Studio Code.app/Contents/Resources/app/bin
LOGNAME=ilya
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.7HmaIICWLH/Listeners
HOME=/Users/ilya
SHELL=/bin/zsh
__CF_USER_TEXT_ENCODING=0x1F5:0x0:0x2
TMPDIR=/var/folders/q3/xj33tmqd7fv55fb23d4gc_kh0000gn/T/
XPC_SERVICE_NAME=0
XPC_FLAGS=0x0
ORIGINAL_XDG_CURRENT_DESKTOP=undefined
TERM_PROGRAM=vscode
TERM=xterm-256color
TERM_PROGRAM_VERSION=1.49.1
TERM_SESSION_ID=w0t0p0:A1A81A64-C9BD-4538-9EAF-100F85A7C57D
MAIL=marvin@42.fr
PWD=/Users/ilya/Desktop/school21/minishell
ITERM_PROFILE=Default
SHLVL=1
COLORFGBG=7;0
LC_TERMINAL_VERSION=3.3.9
ITERM_SESSION_ID=w0t0p0:A1A81A64-C9BD-4538-9EAF-100F85A7C57D
LC_CTYPE=UTF-8
LC_TERMINAL=iTerm2
COLORTERM=truecolor
APPLICATION_INSIGHTS_NO_DIAGNOSTIC_CHANNEL=true
OLDPWD=/Users/ilya/Desktop/school21/minishell
LANG=en_GB.UTF-8
VSCODE_GIT_IPC_HANDLE=/var/folders/q3/xj33tmqd7fv55fb23d4gc_kh0000gn/T/vscode-git-8dc7a77b2d.sock
GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh
VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Renderer).app/Contents/MacOS/Code Helper (Renderer)
VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js
_=/Users/ilya/Desktop/school21/minishell/./a.out
*/