/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:00:34 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/10 18:27:46 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_envar(char **envp, char *var)
{
    char **env;
    char *path;

    env = envp; 
    while (*env)
    {
        if (!ft_strncmp(*env, var, ft_strlen(var)))
        {
            path = ft_strchr(*env, '=');
            if (path)
                path++;
            return (path);
        }
        env++;
    }
    return (NULL);
}