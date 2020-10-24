/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:00:34 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/24 16:42:56 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "../includes/minishell.h"

char *get_envar(char *var)
{
    t_list *env;
    char *value;
    char *ret;
    int    flag;

    env = g_env;
    flag = 0;
    ret = NULL;
    if (!ft_strcmp(var, "?"))
        return(ft_itoa((int)g_exit%256));
    if (!ft_strcmp(var, "~"))
    {
        var = ft_strdup("HOME");
        flag = 1;
    }
    while (env)
    {
        if (!ft_strncmp(((t_envar *)(env->content))->key, var, ft_strlen(var)))
        {
            value = ((t_envar *)(env->content))->value;
            ret = ft_strdup(value);
            if (flag)
                free(var);
            return (ret);
        }
        env = env->next;
    }
    if (flag)
    {
        free(var);
        return(g_home);
    }
    return (NULL);
}