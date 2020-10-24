/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_states.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:07:53 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/24 15:07:54 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 		set_states(char c)
{
	set_backslash_state_new(c);
	set_quotes_state_new(c);
}
