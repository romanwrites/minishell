/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:39:20 by mkristie          #+#    #+#             */
/*   Updated: 2020/11/06 13:29:27 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool	g_dquote;
_Bool	g_squote;
_Bool	g_backslash;
int		g_backslash_time;

t_list	*g_env;
char	*g_input;
char	*g_home;
int		g_isfork;
long long g_exit;
int		g_timer;
pid_t	g_pid;

void		state_bzero(t_parse *state)
{
	state->is_double_quote_open = 0;
	state->is_single_quote_open = 0;
	state->backslash = 0;
	state->backslash_time = 0;
}

void		init(t_mshell *sv)
{
	sv->state = (t_parse *)malloc(sizeof(t_parse) * 1);
	ft_alloc_check(sv->state);
	init_globs();
}

t_mshell	*init_gvars_sig_sv(int argc, char **argv, char **envp)
{
	t_mshell	*sv;

	(void)argc;
	(void)argv;
	g_exit = 0;
	g_timer = 0;
	g_env = env_to_list(envp);
	g_home = get_envar("HOME");
	signal(SIGQUIT, handle_parent_signal);
	signal(SIGINT, handle_parent_signal);
	signal(SIGTERM, SIG_IGN);
	ft_unset((char*[3]){"unset", "OLDPWD", NULL});
	sv = (t_mshell *)malloc(sizeof(t_mshell));
	ft_alloc_check(sv);
	init(sv);
	return (sv);
}

int			main(int argc, char **argv, char **envp)
{
	t_mshell	*sv;
	char		*str;

	str = NULL;
	sv = init_gvars_sig_sv(argc, argv, envp);
	write(0, PROMPT, ft_strlen(PROMPT));
	while (get_next_line(0, &str, 0, 0))
	{
		ft_alloc_check(str);
		if (parse_input(str, sv))
		{
			free(str);
			str = NULL;
			write(0, PROMPT, ft_strlen(PROMPT));
			continue ;
		}
		process_cmd(sv);
		write(0, PROMPT, ft_strlen(PROMPT));
		free_all_lists(sv);
		free(str);
		str = NULL;
	}
	if (*(str) == '\0')
		write(2, "exit\n", ft_strlen("exit\n"));
	return (0);
}
