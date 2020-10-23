/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_mshell.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 04:11:56 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/07 04:13:58 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_MSHELL_H
# define ENGINE_MSHELL_H
#include "structs_mshell.h"

void	state_bzero(t_parse *state);
_Bool	check_quotes_state(t_parse *state);
int		gnl_minishell(int fd, char **line, char *shell_str, _Bool (*check_quotes_state)(t_parse *state));
void	process_cmd(t_mshell *sv);

#endif