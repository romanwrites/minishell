/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mshell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 17:39:05 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/28 19:53:02 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MSHELL_H
# define PARSE_MSHELL_H

# define BACKSLASH 92
# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39
# define SEMICOLON 59
# define PIPE 124
# define DOLLAR 36
# define GRAVE_ACCENT 96
# define REDIR_LEFT 60
# define REDIR_RIGHT 62
# define REDIR_RIGHT_DOUBLE ">>"
# define NEWLINE 10
# define SYNTAX_ERROR "bash: syntax error near unexpected token"
# define SYNTAX_UNEXP_NL "bash: syntax error near unexpected token `newline'"

/*
** alloc_pipe_list.c
*/
t_dlist_pipe	*alloc_pipe_list(char **ptr, int i);

/*
** alloc_token_list.c
*/
t_token			*alloc_token_list(char **ptr);

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
** check_tokens_syntax.c
*/
_Bool			check_tokens_syntax(t_mshell *sv);

/*
** get_sh_list.c
*/
t_dlist_sh		*get_sh_list(char **semicolons2d, int i, t_mshell *sv);

/*
** handle_dollar.c
*/
void			handle_dollar(t_open_q *o, size_t i);
void			get_env_val(t_open_q *o, size_t i, size_t j);
void			append_dollar_after_backslash(t_open_q *o, size_t i, size_t j);
void			get_several_dollars(t_open_q *o, size_t i);

/*
** open_quotes.c
*/
void			open_quotes(t_token *token);

/*
** open_quotes2.c
*/
char			*open_quotes_str(t_open_q *o, size_t i);

/*
** open_quotes_utils.c
*/
char			*just_tilde(t_open_q *o, int i);
_Bool			is_env_val_after_dollar(char c);
void			append_tilda(t_open_q *o, size_t i);

/*
** parse.c
*/
_Bool			parse_input(char *str, t_mshell *sv);
_Bool			ret_syntax_err(void);
size_t			len_without_newlines(const char *ptr);
void			append_line(char **ptr, char **append_this);

/*
** parse_env.c
*/
int				get_env_from_str(const char *str);
size_t			get_dollars_end(const char *str);

/*
** split_by_char.c
*/
char			**split_by_char(char c, char *str);

/*
** split_by_commands.c
*/
char			**split_command(const char *str_input);

/*
** split_by_commands_utils.c
*/
_Bool			is_after_redir_semi_check(const char *str, int i);
_Bool			is_after_redir_or_pipe(const char *str, int i);
_Bool			is_after_redir(const char *str, int i);
_Bool			is_double_redir(const char *str, int i);
_Bool			is_pipe_or_single_redir(const char *str, int i);

#endif
