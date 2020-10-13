/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:00:34 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/13 16:05:53 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_envar(char **envp, char *var)
{
    char **env;
    t_list *list;
    char *value;
    char *ret;

    env = envp;
    list = g_exp;
    ret = NULL;
    while (*env)
    {
        if (!ft_strncmp(*env, var, ft_strlen(var)))
        {
            value = ft_strchr(*env, '=');
            if (value)
            {
                value++;
                ret = ft_strdup(value);
            }
            return (ret);
        }
        env++;
    }
    while(list)
    {
        list = list->next;
    }
    return (NULL);
}