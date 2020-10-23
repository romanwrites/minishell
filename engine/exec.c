#include "../includes/minishell.h"

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
		ft_exit(0);
	else if (!(strcmp(cmd[0], "cd")))
		ft_cd(cmd[1]);
	else if (!(strcmp(cmd[0], "unset")))
		ft_unset(cmd[1]);
	else
		handle_cmd(cmd);
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
	/*
	if (is_redir)
	{
		if(!ft_strcmp(is_redir, ">"))
		{
			fd = open(file, O_CREAT | O_TRUNC | O_WRONLY | S_IRUSR | S_IWUSR | S_IROTH);
			if(fd)
				dup2(fd, 1);
		}
		else if(!ft_strcmp(is_redir, "<"))
		{
			fd = open(file, O_RDONLY | S_IRUSR | S_IWUSR | S_IROTH);
			if(fd)
				dup2(fd, 0);
		}
		else
		{
			fd = open(file, O_CREAT | O_APPEND | O_WRONLY | S_IRUSR | S_IWUSR | S_IROTH);
			if(fd)
				dup2(fd, 1);
		}
		if(!fd)
		{
			if (!ft_strcmp(is_redir, "<"))
				dup2(savestdin, 0);
			else
				dup2(savestdout, 1);
			return ;
		}
		*/
	if(fd != -1)
	{
		if (!ft_strcmp(is_redir, "<"))
			dup2(fd, 0);
		else
			dup2(fd, 1);
		pid = fork();
    	if (pid == 0)
    	{
			signal(SIGQUIT, handle_child_signal);
			signal(SIGINT, handle_child_signal);
			close(fd);
			execute(cmd);
			exit(0);
		}
		else
		{
			wait(NULL);
			close(fd);
			if (!ft_strcmp(is_redir, "<"))
				dup2(savestdin, 0);
			else
				dup2(savestdout, 1);
		}
	}
	else
		execute(cmd);
}