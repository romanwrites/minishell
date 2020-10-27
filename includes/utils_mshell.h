/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mshell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:56:37 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/27 16:17:00 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_MSHELL_H
# define UTILS_MSHELL_H

# include "minishell.h"

void				ft_alloc_check(void *ptr);
void				exit_error_message(char *str);
void				print_2d_array(char **arr2d);
void				ft_trim_2d(char ***arr_2d);
char				**ft_trim_2d_cpy(char **arr_2d);
int					compare_key(t_envar *a, t_envar *b);
t_token				*token_new(char *content, t_token **prev);
t_dlist_pipe		*pipe_new(t_token *content, t_dlist_pipe **prev);
t_dlist_sh			*sh_new(t_dlist_pipe *content, t_dlist_sh **prev);
void 				print_token_list(t_token *token);
void				print_everything(t_mshell *sv);
void				print_error(char *str);
void 				reset_newlines(char *str);
void				free_all_lists(t_mshell *sv);
void 				set_heads(t_mshell *sv);
void 				set_states(char c);
void				set_backslash_state_new(char c);
_Bool				is_backslash_active();
void				set_quotes_state_new(char c);
_Bool				is_open_quote();
void				init_globs();
void				*ft_strdup_and_check(const char *str);

/*
** states_first_lvl.c
*/
_Bool	        	is_any_quote_open(t_parse *state_check);
void	        	set_quotes_state(t_parse *state_check, int j, const char *str);
_Bool	        	is_backslash_pressed(t_parse *state_check);
void	        	set_backslash_state(t_parse *state_check, char c);
int                 check_numeric(char *str);
long long		    ft_atoll(char *str);
unsigned long long  ft_atoull(char *str, int *minus);


#endif
