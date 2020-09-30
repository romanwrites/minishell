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

void		parse_start(t_mshell *sv);
char		**split_by_quotes(t_mshell *sv);
char		**split_by_char(t_mshell *sv, char c, char *str);
int			count_2d_lines(char **arr2d);

#endif