/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_mshell.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:48:38 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/25 19:57:52 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_MSHELL_H
#define STRUCTS_MSHELL_H

#include "libft.h"
#include "minishell.h"

typedef struct	s_parse {
	_Bool		backslash;
	_Bool		is_double_quote_open;
	_Bool		is_single_quote_open;
	int			backslash_time;
}				t_parse;

typedef struct	s_mshell {
	char		*content;
	int			i;
	t_parse		*state;
	t_dlist		*dlst_head;
}				t_mshell;

#endif
