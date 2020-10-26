#include "../includes/minishell.h"

void all_to_lower(char **cmd)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while(cmd[i])
	{
		while(cmd[i][x])
		{
			cmd[i][x] = ft_tolower(cmd[i][x]);
			x++;
		}
		i++;
		x = 0;
	}
}

void 	execute(char **cmd)
{
	if (!(strcmp(cmd[0], "export")))
		ft_export(cmd[1]);
	else if (!(strcmp(cmd[0], "env")))
		ft_env();
	else if (!(strcmp(cmd[0], "pwd")))
		ft_pwd();
	else if (!(strcmp(cmd[0], "echo")))
		ft_echo(cmd);
	else if (!(strcmp(cmd[0], "exit")))
		ft_exit(cmd);
	else if (!(strcmp(cmd[0], "cd")))
		ft_cd(cmd[1]);
	else if (!(strcmp(cmd[0], "unset")))
		ft_unset(cmd[1]);
	else
	{
		all_to_lower(cmd);
		handle_cmd(cmd);
	}
}

int	handle_redir(char *is_redir, char *file)
{
	int fd;

	fd = -1;
	if (is_redir)
	{
		if(!ft_strcmp(is_redir, ">"))
			fd = open(file, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if(!ft_strcmp(is_redir, "<"))
			fd = open(file, O_RDONLY);
		else
			fd = open(file, O_APPEND | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	return (fd);
}

void 	execute_command(char **cmd, char *is_redir, int fd)
{
	pid_t pid;

    int savestdout = dup(1);
    int savestdin = dup(0);

	if(fd != -1)
	{
		if (!ft_strcmp(is_redir, "<"))
			dup2(fd, 0);
		else
			dup2(fd, 1);
		execute(cmd);//
		if (!ft_strcmp(is_redir, "<"))//
			dup2(savestdin, 0);//
		else//
			dup2(savestdout, 1);//
	}
	else
		execute(cmd);
}