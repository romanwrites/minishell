/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_kv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:24:24 by lhelper           #+#    #+#             */
/*   Updated: 2020/10/28 19:57:07 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		compare_key(t_envar *a, t_envar *b)
{
	return (ft_strncmp(a->key, b->key, \
			max_len(ft_strlen(a->key), ft_strlen(b->key))));
}
