/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 06:44:16 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/28 21:13:05 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include "minishell.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int				get_next_line(int fd, char **line, _Bool f, ssize_t bytes_read);
size_t			ft_strlen_gnl(const char *s);
char			*ft_strdup_gnl(const char *s1);
char			*ft_strchr_gnl(const char *s, int c);
char			*ft_strjoin_gnl(char *s1, char *s2);
char			*ft_substr_gnl(char const *s, unsigned int start, size_t len);

/*
** get_next_line_utils_2.c
*/
char			*gnl_strjoin_free_null_ret(char *s1_holder);
_Bool			write_b_b(void);
void			process_g_input(void);
int				process_nl(char *newline_ptr);

extern	char	*g_input;

#endif
