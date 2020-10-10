#include "includes/minishell.h"
pid_t g_pid;

void	echo_assert_test()
{
	printf("_________BACKSLASH________\n");
	ft_echo("", 0);
	//ft_echo("su\p", 0); //su/p warning: unknown escape sequence '\p' [-Wunknown-escape-sequence]
	ft_echo("su\tp", 0);
	ft_echo("su\np", 0);
	ft_echo("su\0p", 0); //sup
	ft_echo("sup\n", 0);
}

void sig_handler(int signum)
{
	if (!g_pid)
	{
		printf("%d KUKU\n", signum);
		exit(0);
	}
	else
		printf("PARENT\n");
}

int main(int argc, char **argv, char **envp)
{
	t_list *list;
	t_list *tmp;
	//echo_assert_test();
	//ft_pwd();
	g_env = envp;
	g_exp = NULL;
	//signal(SIGINT, sig_handler);
	//g_pid = fork();
	//while(1);
	if (argv[1][0] == 'e' && argv[1][1] == 'n' && argv[1][2] == 'v' && argv[1][3] == '\0')
	{
		ft_env();
		return 0;
	}
	if (!(strcmp(argv[1], "export")))
	{
		//printf("\n---------------EXPORT2----------------\n");
		//if (argc < 3)
		//	ft_export(0);
		//else
		//	ft_export(argv[2]);
		printf("\n---------------EXPORT1----------------\n");
			ft_export("LEL=111 LOL=000");
		printf("\n---------------EXPORT2----------------\n");
			ft_export("LAL=666");
		printf("\n---------------UNSET0----------------\n");
			ft_unset(" LEL LAL LOL ");
		printf("\n---------------ENV----------------\n");
		ft_env();
		printf("\n---------------EXPORT0----------------\n");
			ft_export(NULL);
		return 0;
	}
	if (!(strcmp(argv[1], "path")))
	{
		printf("%s\n", get_envar(g_env, "PATH"));
	}
	ft_cd(argv[1]);
	//ft_pwd();
	ft_exit(0);
	printf("ur exit doesnt work");
    return 0;
}