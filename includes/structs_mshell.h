/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_mshell.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:48:38 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/30 21:07:15 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_MSHELL_H
#define STRUCTS_MSHELL_H

#include "../libft/libft.h"
#include "minishell.h"

typedef struct				s_open_q {
	size_t					i;
	size_t 					save;
	char					*new_line;
	char					*append_this;
	char 					*str;
	char 					*tab;
}							t_open_q;

typedef struct				s_parse {
	_Bool					backslash;
	_Bool					is_double_quote_open;
	_Bool					is_single_quote_open;
	int						backslash_time;
}							t_parse;

typedef struct				s_token {
	char 					*content;
	_Bool					is_diff;
	_Bool					tick;
	struct s_token			*next;
	struct s_token			*prev;
}							t_token;

typedef struct				s_dlist_pipe {
	t_token					*token;
	t_token					*token_head;
	struct s_dlist_pipe		*next;
	struct s_dlist_pipe		*prev;
}							t_dlist_pipe;

typedef struct				s_dlist_sh {
	t_dlist_pipe			*tdlst_pipe;
	t_dlist_pipe			*tdlst_pipe_head;
	struct s_dlist_sh		*next;
	struct s_dlist_sh		*prev;
}							t_dlist_sh;

typedef struct				s_mshell {
	t_parse					*state;
	t_dlist_sh				*sh;
	t_dlist_sh				*sh_head;
}							t_mshell;

typedef struct				s_envar
{
    char					*key;
    char					*value;
}							t_envar;

#endif
