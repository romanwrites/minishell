/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_mshell.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:14:42 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/30 18:14:43 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_MSHELL_H
# define BUILTIN_MSHELL_H

# include "minishell.h"


extern  t_list	*g_env;
extern	pid_t	g_pid;
extern	char	*g_home;
extern  int		g_stdin;
extern  int		g_stdout;


//f


/*
** builtin_utils.c
*/
void			free_nothing(void *to_free);
void			free_content(void *to_free);
t_list			*ft_merge_lists(t_list *dst, t_list *src);
int				find_key_replace_val(t_list **lst, char *key, char *value);
t_list			*env_to_list(char **envp);

/*
** ft_cd.c
*/
void			ft_cd(char *str);

/*
** ft_echo.c
*/
void			ft_echo(char **str);

/*
** ft_env.c
*/
void			ft_env(void);

/*
** ft_pwd.c
*/
void			ft_pwd(void);

/*
** ft_exit.c
*/
void			ft_exit(char **cmd);

/*
** ft_export.c
*/
void			ft_export(char *arg);



char	**alloc_mem_env(int lines, int max_len, char *arg);
void	count_lines(int *lines, int *max_len, char *arg);
void	fill_env(char **env_array, char *arg);
void	free_env(char **env_array, int lines);

void	ft_unset(char *arg);
void	print_env(char **env_array);
void	sort_env(char **env_array, int lines, int max_len);

#endif