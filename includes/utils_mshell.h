/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mshell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:56:37 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/30 00:23:19 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_MSHELL_H
# define UTILS_MSHELL_H

void		ft_alloc_check(void *ptr);
void        ft_bell(void);
void		exit_error_message(char *str);
void		print_2d_array(char **arr2d);
void		ft_trim_2d(char ***arr_2d);

#endif
