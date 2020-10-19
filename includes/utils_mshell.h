/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mshell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:56:37 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/10 18:26:14 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_MSHELL_H
# define UTILS_MSHELL_H

# include "minishell.h"

void		ft_alloc_check(void *ptr);
void        ft_bell(void);
void		exit_error_message(char *str);
void		print_2d_array(char **arr2d);
void		ft_trim_2d(char ***arr_2d);
int         compare_key(t_envar *a, t_envar *b);
t_token		*new_token(void *content, t_token **prev);

t_dlist_sh		*ft_dlst_sh_new(t_token *content, t_dlist_sh **prev);

#endif
