/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:40:51 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/28 19:56:36 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			chr_join(char **str, char c)
{
	char		append[2];
	char		*new_str;

	append[0] = c;
	append[1] = '\0';
	new_str = ft_strjoin(*str, append);
	free(*str);
	*str = new_str;
}
