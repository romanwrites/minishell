/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mshell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:56:37 by mkristie          #+#    #+#             */
/*   Updated: 2020/11/06 14:57:55 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_MSHELL_H
# define UTILS_MSHELL_H

# include "minishell.h"

/*
** alloc_and_check.c
*/
char				*ft_substr_and_chk(char const *str, \
										unsigned int start, size_t len);
void				*ft_strdup_and_check(const char *str);
char				*ft_itoa_and_chk(int n);
t_list				*ft_lstnew_n_chk(void *content);
void				*malloc_n_chk(size_t size);

/*
** alloc_and_check2.c
*/
t_list				*ft_lstnew_kv_n_chk(void *content);
char				**ft_split_n_chk(char *str, char c);
char				*ft_strjoin_n_chk(char *s1, char *s2);

/*
** check_numeric.c
*/
int					check_numeric(char *str);

/*
** chr_join.c
*/
void				chr_join(char **str, char c);

/*
** compare_kv.c
*/
int					compare_key(t_envar *a, t_envar *b);

/*
** count_2d_lines.c
*/
int					count_2d_lines(char **arr2d);

/*
** dlst_pipe.c
*/
t_dlist_pipe		*pipe_new(t_token *content, t_dlist_pipe **prev);

/*
** dlst_sh.c
*/
t_dlist_sh			*sh_new(t_dlist_pipe *content, t_dlist_sh **prev);

/*
** exit_error_message.c
*/
void				exit_error_message(char *str);

/*
** free_all_lists.c
*/
void				free_all_lists(t_mshell *sv);

/*
** free_and_null.c
*/
void				free_and_null(char **str);

/*
** ft_alloc_check.c
*/
void				ft_alloc_check(void *ptr);

/*
** ft_atoll.c
*/
long long			ft_atoll(char *str);

/*
** ft_atoull.c
*/
unsigned long long	ft_atoull(char *str, int *minus);

/*
** ft_lstnew_kv.c
*/
t_list				*ft_lstnew_kv(void *content);

/*
** ft_trim_2d_cpy.c
*/
char				**ft_trim_2d_cpy(char **arr_2d);

/*
** get_envar.c
*/
char				*get_envar(char *var);

/*
** handle_cmd1.c
*/
void				myclosedir(t_norm *n);
void				get_paths(t_norm *n);
void				init_envp(int *i, t_norm **n);
void				cmd_not_found(t_norm *n, char **args);
void				command_found(int i, t_norm *n, char **args);

/*
** handle_cmd2.c
*/
void				free_splitted(t_norm *n);
void				process_slash(int status, char *tmp, \
									char **args, char **envp);
char				*find_cmd(char *path);
int					list_size(void);
char				**list_to_env(void);

/*
** handle_cmd3.c
*/
void				free_envp(char **envp);
/*
** is_str.c
*/
_Bool				is_some_redir(char *str);

/*
** print_2d_array.c
*/
void				print_2d_array(char **arr2d);

/*
** print_error.c
*/
void				print_error(char *str);

/*
** print_everything.c
*/
void				print_everything(t_mshell *sv);

/*
** print_token_list.c
*/
void				print_token_list(t_token *token);

/*
** process_cmd1.c
*/
void				add_token(t_norma *n, t_token *token);
t_token				*next_pipe(t_mshell *sv);
void				next_semicolon(t_mshell *sv);
void				execute_child(t_norma *n);
void				execute_parent(t_norma *n);

/*
** process_cmd2.c
*/
t_token				*zero_index_quotes(t_mshell *sv, t_norma *n);
void				left_or_right(t_norma *n, t_token *token);
void				preexecute_pipe(t_norma *n);
void				fill_before_pipe(t_norma *n);
void				print_no_file_dir(char *str);

/*
** reset_newlines.c
*/
void				reset_newlines(char *str);

/*
** set_heads.c
*/
void				set_heads(t_mshell *sv);

/*
** set_states.c
*/
void				set_states(char c);

/*
** signal.c
*/
void				handle_parent_signal(int signal);

/*
** states.c
*/
void				init_globs();
void				set_backslash_state_new(char c);
_Bool				is_bs_active();
void				set_quotes_state_new(char c);
_Bool				is_open_quote();

/*
** states_first_lvl.c
*/
_Bool				is_any_quote_open(t_parse *state_check);
void				set_quotes_state(t_parse *state_check, int j, \
										const char *str);
_Bool				is_backslash_pressed(t_parse *state_check);
void				set_backslash_state(t_parse *state_check, char c);

/*
** token.c
*/
t_token				*token_new(char *content, t_token **prev);

#endif
