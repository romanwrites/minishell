/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mshell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 17:39:05 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/27 16:16:18 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MSHELL_H
# define PARSE_MSHELL_H

# define BACKSLASH 92
# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39
# define SPACE 32
# define SEMICOLON 59
# define PIPE 124
# define DOLLAR 36
# define GRAVE_ACCENT 96
# define EXIT_CODE 63
# define INPUT 60
# define OUTPUT 62
# define AND 38
# define REDIR_LEFT 60
# define REDIR_RIGHT 62
# define REDIR_RIGHT_DOUBLE ">>"
# define NEWLINE 10

_Bool		parse_input(char *str, t_mshell *sv);
char		**split_by_char(char c, char *str, t_mshell *sv);
int			count_2d_lines(char **arr2d);
char		**split_command(const char *str_input);
_Bool		is_redir_or_pipe(char c);
_Bool		is_valid_syntax(char pre, char cur, char next);

char		*realloc_without_newlines(char **append_this);
size_t		len_without_newlines(const char *ptr);

char		*open_quotes_str(const char *str_src);
void		open_quotes(t_token *token);
void		open_quotes_new(t_token *token);

void		parse_env();
void        append_line(char **ptr, char **append_this);
size_t		get_dollars_end(const char *str);
int			get_env_from_str(const char *str);
_Bool		is_after_redir_semi_check(const char *str, int i);
_Bool		is_after_redir_or_pipe(const char *str, int i);
_Bool 		is_after_redir(const char *str, int i);
_Bool		is_double_redir(const char *str, int i);
_Bool		is_pipe_or_single_redir(const char *str, int i);

/*
** check_syntax.c
*/
_Bool			check_syntax_errors(const char *str);
_Bool			other_conditions(const char *str, int i);
_Bool			check_sequence_full(char c1, char c2);
_Bool			check_sequence_semi(char c1, char c2);

/*
** check_syntax2.c
*/
_Bool			check_redirs_only(const char *str);
_Bool			check_syntax_2d(char **ptr);
_Bool			check_syntax_by_indexes(const char *str);

/*
** get_sh_list.c
*/
t_dlist_sh			*get_sh_list(char **semicolons2d, int i, t_mshell *sv);

/*
** alloc_pipe_list.c
*/
t_dlist_pipe	*alloc_pipe_list(char **ptr);

/*
** alloc_token_list
*/
t_token			*alloc_token_list(char **ptr);

#endif