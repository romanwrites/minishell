/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 17:53:17 by mkristie          #+#    #+#             */
/*   Updated: 2020/11/05 18:28:32 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# define STDOUT 1
# define STDIN 0
# define PROMPT "bash-3.2$ "
# define PRINT_ERROR_FD 2
# define PROM "bash: "

# include "structs_mshell.h"
# include "utils_mshell.h"
# include "parse_mshell.h"
# include "engine_mshell.h"
# include "builtin_mshell.h"

# include "../libft/libft.h"
# include "get_next_line.h"

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>

extern _Bool				g_dquote;
extern _Bool				g_squote;
extern _Bool				g_backslash;
extern int					g_backslash_time;
extern long long			g_exit;
extern int					g_timer;
extern _Bool				g_bp;

void		handle_cmd(char **cmd);
char		**list_to_env();
void		execute_command(char **cmd, int fd, int filedes);
int			handle_redir(char *is_redir, char *file);
int			status_return(int status);
void		refresh_env(void);
void		timer(void);

#endif
