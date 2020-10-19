#include "includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *ls[] = {"ls", "-la", NULL};
    char *cat[] = {"cat", "-e", NULL};
    pid_t pid;
    int fd;

    int savestdout = dup(1);
    int savestdin = dup(0);
	if (argc != 3)
		return (1);
	if (!strcmp(argv[1], "1"))
	{
		write(1, ">\n", 2);
		fd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY | S_IRUSR | S_IWUSR | S_IROTH);
		dup2(fd, 1);
		pid = fork();
    	if (pid == 0)
    	{
			close(fd);
			execve("/bin/ls", ls, envp);
		}
		else
		{
			wait(NULL);
			close(fd);
			dup2(savestdout, 1);
			write(1, "\nendl\n", 6);
			return (0);
		}
	}
	else if (!strcmp(argv[1], "2"))
	{
		write(1, ">>\n", 3);
		fd = open(argv[2], O_CREAT | O_APPEND | O_WRONLY | S_IRUSR | S_IWUSR | S_IROTH);
		dup2(fd, 1);
		pid = fork();
    	if (pid == 0)
    	{
			close(fd);
			execve("/bin/ls", ls, envp);
		}
		else
		{
			wait(NULL);
			close(fd);
			dup2(savestdout, 1);
			write(1, "\nendl\n", 6);
			return (0);
		}
	}
	else if (!strcmp(argv[1], "0"))
	{
		write(1, "<\n", 2);
		fd = open(argv[2], O_RDONLY | S_IRUSR | S_IWUSR | S_IROTH);
		dup2(fd, 0);
		pid = fork();
    	if (pid == 0)
    	{
			close(fd);
			execve("/bin/cat", cat, envp);
		}
		else
		{
			wait(NULL);
			close(fd);
			dup2(savestdin, 0);
			write(1, "\nendl\n", 6);
			return (0);
		}
	}
	else
		return (1);
}