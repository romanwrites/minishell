/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:33:29 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/25 16:19:14 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *str, int flag_n)
{
	write(1, str, ft_strlen(str));
	if (!flag_n)
		write(1, "\n", 1);
}

void	ft_pwd()
{
	char *path;

	path = getcwd(path, PATH_MAX);
	printf("%s\n", path);
	//free(path);
}
void	ft_cd(char *str)
{
	char *path;
	char *newPath;
	int len;//
	DIR *dir;
	struct dirent *entry;
	
	dir = NULL;
	/*
	path = getcwd(path, PATH_MAX);
	printf("%s\n", path);
	chdir(str);
	newPath = getcwd(newPath, PATH_MAX);
	printf("%s\n", newPath);
	len = (ft_strlen(path) > ft_strlen(newPath)) ? ft_strlen(path) : ft_strlen(newPath);
	if (!(ft_memcmp(path, newPath, len)))
		printf("erorr: %s\n", strerror(2));
	*/
	printf("ftcd: %s\n", str);
	printf("%p\n", dir);
	dir = opendir(str);
	printf("%p\n", dir);
	if (!dir)
	{
		printf("erorr: %s\n", strerror(errno));
		exit(1);
	}

    while ( (entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    };

    closedir(dir);
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	int len = ft_strlen(argv[1]) + 1;
	char *str = malloc(len);
	ft_bzero(str, len);
	memcpy(str, argv[1], len);
    ft_echo(argv[1], atoi(argv[2]));
	printf("arg0: %s\n", argv[1]);
	ft_pwd();//SOMEHOW changes argv[1]
	printf("main: %s\n", str);
	printf("arg1: %s\n", argv[1]);
	ft_cd(str);
	free(str);
    return 0;
}