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

void	init(t_mshell	*sv)
{
	sv->arr3d = NULL;
	sv->content = NULL;
}

int     main()
{
	t_mshell	*sv;

	sv = (t_mshell *)malloc(sizeof(t_mshell));
	ft_alloc_check(sv);
	init(sv);

	parse_start(sv);
}