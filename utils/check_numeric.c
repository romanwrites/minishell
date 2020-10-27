/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_numeric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:38:39 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/24 17:07:42 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_numeric(char *str)
{
    int i;

    i = 0;
    if (ft_strlen(str) > 20)
        return (1);
    if (str[i] != '-' && !ft_isdigit(str[i]))
        return (1);
    i++;
    while(str[i])
    {
        if(!ft_isdigit(str[i]))
            return (1);
        i++;
    }
    return (0);
}