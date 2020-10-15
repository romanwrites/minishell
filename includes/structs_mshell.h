/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_mshell.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:48:38 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/11 19:21:29 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_MSHELL_H
#define STRUCTS_MSHELL_H

#include "../libft/libft.h"
#include "minishell.h"

extern _Bool	g_dquote;
extern _Bool	g_squote;
extern _Bool	g_backslash;
extern int		g_backslash_time;

typedef struct		s_char
{
	char			*original;
	char			*copy;
	int				index;
}					t_char;

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
	void        *envp_mshell;
}				t_mshell;

typedef struct  s_envar
{
    char *key;
    char *value;
}               t_envar;

#endif
