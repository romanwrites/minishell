/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:00:34 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/13 23:43:58 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "../includes/minishell.h"

char *get_envar(char *var)
{
    t_list *env;
    char *value;
    char *ret;

    env = g_env;
    ret = NULL;
    while (env)
    {
        if (!ft_strncmp(((t_envar *)(env->content))->key, var, ft_strlen(var)))
        {
            value = ((t_envar *)(env->content))->value;
            ret = ft_strdup(value);
            return (ret);
        }
        env = env->next;
    }
    return (NULL);
}