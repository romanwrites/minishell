/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_kv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:24:24 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/13 18:03:42 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "../includes/minishell.h"

int		compare_key(t_envar *a, t_envar *b)
{
	return(ft_strncmp(a->key, b->key, max_len(ft_strlen(a->key), ft_strlen(b->key))));
}