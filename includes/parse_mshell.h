/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mshell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 17:39:05 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/25 19:58:49 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MSHELL_H
# define PARSE_MSHELL_H

# define BACK_SLASH 92
# define DOUBLE_QUOTES 34
# define SINGLE_QUOTES 39
# define SPACE 32
# define SEMICOLON 59
# define PIPE 124
# define DOLLAR 36
# define EXIT_CODE 63
# define INPUT 60
# define OUTPUT 62
# define AND 38
# define PARENTHESIS_OPEN 40
# define PARENTHESIS_CLOSE 41
# define WILDCARD 42

void		parse_input(t_mshell *sv);
char		**split_by_char(t_mshell *sv, char c, char *str);
int			count_2d_lines(char **arr2d);
_Bool		is_backslash_pressed(t_parse *state_check);
void		set_backslash_state(t_parse *state_check, char c);
void		set_quotes_state(t_parse *state_check, int j, const char *str);
_Bool		is_any_quote_open(t_parse *state_check);
char		**split_command(t_mshell *sv, char *str);
void		set_nl_cpy(char **str, int i);
_Bool		is_redir_or_pipe(char c);
_Bool		is_valid_syntax(char pre, char cur, char next);

#endif