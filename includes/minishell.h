/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 17:53:17 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/12 10:57:13 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# define STDOUT 1
# define STDIN 0
# define PROMPT "zaebash: "

# include "structs_mshell.h"
# include "utils_mshell.h"
# include "parse_mshell.h"
# include "engine_mshell.h"
# include "builtin_mshell.h"

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
# include <fcntl.h>
# include <stdio.h> //

#endif