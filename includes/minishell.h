#ifndef MINISHELL_H

# define MINISHELL_H

# include "utils_mshell.h"
# include "structs_mshell.h"
# include "parse_mshell.h"

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/errno.h>
# include <signal.h>
# include <stdio.h> //

extern  t_list  *g_exp;//added by export env vars
extern  char    **g_env;

typedef struct  s_envar
{
    char *key;
    char *value;
}               t_envar;

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
void	ft_list_sort(t_list **begin_list, int (*cmp)());
void	ft_pwd();
void	ft_unset(char *arg);
void	print_env(char **env_array);
void	sort_env(char **env_array, int lines, int max_len);


#endif