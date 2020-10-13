#ifndef BUILTIN_MSHELL_H
# define BUILTIN_MSHELL_H

# include "minishell.h"

extern  t_list  *g_exp;//added by export env vars
extern  t_list	*g_env;
extern	pid_t	g_pid;

char	**alloc_mem_env(int lines, int max_len, char *arg);
int		compare_key(t_envar *a, t_envar *b);
void	count_lines(int *lines, int *max_len, char *arg);
t_list	*env_to_list(char **envp);
void	fill_env(char **env_array, char *arg);
void	free_content(void *to_free); //should be pointed be del() in ft_lstclear()
void	free_env(char **env_array, int lines);
void	ft_cd(char *str);
void	ft_echo(char *str, int flag_n);
void	ft_env();
void	ft_exit(int exit_code);
void	ft_export(char *arg);
void	ft_pwd();
void	ft_unset(char *arg);
char    *get_envar(char *var);
void	print_env(char **env_array);
void	sort_env(char **env_array, int lines, int max_len);

#endif