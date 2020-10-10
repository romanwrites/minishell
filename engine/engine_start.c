/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:39:20 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/10 18:57:28 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	state_bzero(t_parse *state)
{
	state->is_double_quote_open = 0;
	state->is_single_quote_open = 0;
	state->backslash = 0;
	state->backslash_time = 0;
}

void	init(t_mshell	*sv)
{
	sv->content = NULL;
	sv->i = 0;
	sv->state = (t_parse *)malloc(sizeof(t_parse) * 1); // free after parse
	ft_alloc_check(sv->state);
	state_bzero(sv->state);
}

int     main(int ac, char **av, char **envp)
{
	t_mshell	*sv;

	(void)ac;
	(void)av;

	sv = (t_mshell *)malloc(sizeof(t_mshell));
	ft_alloc_check(sv);
	init(sv);
	sv->envp_mshell = (void *)envp;

	int fd = open("parse_tests.txt", O_RDONLY);
	while (get_next_line(0, &sv->content))
	{
		ft_alloc_check(sv->content);
		parse_input(sv);
		free(sv->content);
		sv->content = NULL;
	}
	parse_input(sv);
	if (sv->content)
	    free(sv->content);
	sv->content = NULL;
	free(sv);
	sv = NULL;
	sleep(30);
}