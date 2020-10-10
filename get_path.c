/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:00:34 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/10 10:18:30 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char *get_path(char **envp)
{
    char **env;
    char *path;

    env = envp; 
    while (*env)
    {
        if (!ft_strncmp(*env, "PATH", ft_strlen("PATH")))
        {
            path = ft_strchr(*env, '=');
            path++;
            return (path);
        }
        env++;
    }
    return (NULL);
}