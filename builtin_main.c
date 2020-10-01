#include "includes/minishell.h"

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

int main(int argc, char **argv, char **envp)
{
	t_list *list;
	t_list *tmp;

	//echo_assert_test();
	//ft_pwd();
	printf("+++++++++++++++++BEGIN+++++++++++++++++\n");
	g_env = envp;
	g_exp = NULL;
	//printf("\n---------------EXPORT0----------------\n");
	//ft_export(0);
	//printf("\n---------------ENV0----------------\n");
	//ft_env();
	//printf("\n---------------EXPORT1----------------\n");
	//ft_export(0);
	//printf("\n---------------ENV1----------------\n");
	//ft_env();
	if (argv[1][0] == 'e' && argv[1][1] == 'n' && argv[1][2] == 'v' && argv[1][3] == '\0')
	{
		ft_env();
		return 0;
	}
	if (!(strcmp(argv[1], "unset")))
	{
		if (!(argv[3]))
			ft_unset(0);
		else
			ft_unset(argv[3]);
	}
	if (!(strcmp(argv[1], "export")))
	{
		//printf("\n---------------EXPORT2----------------\n");
		//if (argc < 3)
		//	ft_export(0);
		//else
		//	ft_export(argv[2]);
		printf("\n---------------EXPORT3----------------\n");
			ft_export("LOL=666");
		printf("\n---------------EXPORT3----------------\n");
			ft_export("LOL=666");
		printf("\n---------------EXPORT3----------------\n");
			ft_export("LOL=666");
		printf("\n---------------ENV2----------------\n");
		ft_env();
		return 0;
	}
	//ft_cd(argv[1]);
	ft_exit(0);
	printf("ur exit doesnt work");
    return 0;
}
