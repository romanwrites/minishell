/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:00:34 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/28 20:36:18 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_envar(char *var)
{
    t_list	*env;
    char	*value;
    char	*ret;
    int		flag;

    env = g_env;
    flag = 0;
    ret = NULL;
    if (!ft_strcmp(var, "?"))
        return(ft_itoa_and_chk((int)g_exit%256));
    if (!ft_strcmp(var, "~"))
    {
        var = ft_strdup_and_check("HOME");
        flag = 1;
    }
    while (env)
    {
        if (!ft_strncmp(((t_envar *)(env->content))->key, var, ft_strlen(var)))
        {
            value = ((t_envar *)(env->content))->value;
            ret = ft_strdup_and_check(value);
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
