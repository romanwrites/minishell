/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_mshell.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:48:38 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/21 19:25:08 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_MSHELL_H
#define STRUCTS_MSHELL_H

#include "../libft/libft.h"
#include "minishell.h"

typedef struct				s_char
{
	char					*original;
	char					*copy;
	int						index;
}							t_char;

typedef struct				s_parse {
	_Bool					backslash;
	_Bool					is_double_quote_open;
	_Bool					is_single_quote_open;
	int						backslash_time;
}							t_parse;

typedef struct				s_token {
	char 					*content;
	_Bool					is_diff;
	_Bool					is_handled;//
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
	char					*content;
	int						i;
	t_parse					*state;
	t_dlist_sh				*sh;
	t_dlist_sh				*sh_head;
	void     	   			*envp_mshell;
}							t_mshell;

typedef struct				s_envar
{
    char					*key;
    char					*value;
}							t_envar;

#endif
