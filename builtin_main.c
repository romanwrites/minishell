#include "includes/minishell.h"

char **g_envp;

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

	g_envp = envp;
	//echo_assert_test();
	//ft_pwd();
	list = env_to_list();
	//ft_list_sort(&list, compare_key);
	if (argc == 1)
	{
		//printf("\n");
		while (list)
		{
			printf("%s=%s\n", ((t_envar *)list->content)->key, ((t_envar *)list->content)->value);
			list = list->next;
		}
		return 0;
	}
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
