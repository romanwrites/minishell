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

void 	execute_command(char **cmd)
{
	pid_t pid;
    int fd;

    int savestdout = dup(1);
    int savestdin = dup(0);
	char is_redir = 0;
	char *file = NULL;

	if (is_redir)
	{
		if(is_redir == ">")
		{
			fd = open(file, O_CREAT | O_TRUNC | O_WRONLY | S_IRUSR | S_IWUSR | S_IROTH);
			if(fd)
				dup2(fd, 1);
		}
		else if(is_redir == "<")
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
			return ;
		pid = fork();
    	if (pid == 0)
    	{
			close(fd);
			execute(cmd);
			return ;
		}
		else
		{
			wait(NULL);
			close(fd);
			if (is_redir == "<")
				dup2(savestdin, 0);
			else
				dup2(savestdout, 1);
		}
	}
	else
		execute(cmd);
}