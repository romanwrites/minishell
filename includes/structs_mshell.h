/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_mshell.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:48:38 by mkristie          #+#    #+#             */
/*   Updated: 2020/11/06 13:06:39 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_MSHELL_H
# define STRUCTS_MSHELL_H

# include "../libft/libft.h"
# include "minishell.h"
# include <dirent.h>

typedef struct				s_open_q {
	int						i;
	int						save;
	char					*new_line;
	char					*append_this;
	char					*str;
	char					*tab;
}							t_open_q;

typedef struct				s_parse {
	_Bool					backslash;
	_Bool					is_double_quote_open;
	_Bool					is_single_quote_open;
	int						backslash_time;
}							t_parse;

typedef struct				s_token {
	char					*content;
	_Bool					is_diff;
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

typedef struct				s_prevnext
{
	t_list		*tmp;
	t_list		*ptr_prev;
	t_list		*ptr_next;
	int			first;
}							t_prevnext;

typedef struct				s_norm
{
	char			*to_split;
	char			*tmp;
	char			**path;
	char			**envp;
	DIR				*dir;
	struct dirent	*entry;
	int				status;
}							t_norm;

typedef struct				s_norma
{
	char	**cmd;
	int		fds[2];
	int		fdl;
	int		fdr;
	int		savestdout;
	int		savestdin;
	int		i;
	int		x;
	int		status;
	int		pid;
}							t_norma;

#endif
