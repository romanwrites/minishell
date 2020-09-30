/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:39:20 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/25 19:59:14 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	init(t_mshell	*sv)
{
	sv->arr3d = NULL;
	sv->content = NULL;
	sv->i = 0;
	sv->state = (t_parse *)malloc(sizeof(t_parse) * 1); // free after parse
	ft_alloc_check(sv->state);
	sv->state->is_double_quote_open = 0;
	sv->state->is_single_quote_open = 0;
	sv->state->backslash = 0;
	sv->state->backslash_time = 0;
}

int     main(int ac, char **av, char **envp)
{
	t_mshell	*sv;

	(void)ac;
	(void)av;
	(void)envp;

	sv = (t_mshell *)malloc(sizeof(t_mshell));
	ft_alloc_check(sv);
	init(sv);

	int fd = open("parse_tests.txt", O_RDONLY);
	while (get_next_line(fd, &sv->content))
	{
		ft_alloc_check(sv->content);
		parse_start(sv);
		free(sv->content);
		sv->content = NULL;
	}
	parse_start(sv);
	free(sv->content);
	sv->content = NULL;
	free(sv);
	sv = NULL;
	sleep(30);
}