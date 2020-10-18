#include "includes/minishell.h"
/*
int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    pid_t pid;
    int fd[2];//0 read 1 write

    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        char *greeting = "Hello ";
        write(fd[1], greeting, strlen(greeting));
        close(fd[1]);
        return (0);
    }
    else
    {
        wait(NULL);
        char out[100];
        close(fd[1]);
        read(fd[0], out, 100);
        int i = 6;
        int x = 0;
        while (argv[1][x])
        {
            out[i] = argv[1][x];
            i++;
            x++;
        }
        out[i] = '\0';
        printf("%s\n", out);
        close(fd[0]);
    }
}
*/

int main(int argc, char **argv, char **envp)
{
    if (argc != 2)
        return (1);
    char *ls[] = {"ls", NULL};
    char *cat[] = {"cat", NULL};
    pid_t pid;
    int fd[2];//0 read 1 write

    int savestdout = dup(1);
    int savestdin = dup(0);
    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        execve("/bin/ls", ls, envp);
    }
    else
    {
        wait(NULL);
        char out[1000];
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        execve("/bin/cat", cat, envp);
        //в родительском не будет execve, 
        //просто будут меняться дескрипторы, эта функция должна вызываться в 
        //цикле и на следующей иттерации выполнять execve для второй части пайпа, 
        //но нужны два условия чтобы вначале не читать и в конце не менять дескрипторы? 
        //вроде так, удачи Илюха из будущего
    }
}
