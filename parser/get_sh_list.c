/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sh_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 01:23:37 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/25 01:23:38 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist_sh			*process_new_node(t_dlist_sh *sh)
{
	sh->next = sh_new(NULL, NULL);
	sh = sh->next;
	return (sh);
}

t_dlist_sh			*get_sh_list(char **semicolons2d, int i)
{
	t_dlist_pipe	*dlst_pipe;
	t_dlist_sh		*sh;
	t_dlist_sh		*sh_head;
	char			**tmp_semi;
//	char			**trim_tmp_semi;

	sh = sh_new(NULL, NULL);
	sh_head = sh;
	while (semicolons2d[i])
	{
		tmp_semi = split_by_char(PIPE, semicolons2d[i]);
//		trim_tmp_semi = ft_trim_2d_cpy(tmp_semi);
		if (check_syntax_2d(tmp_semi))
		{
			ft_free2d(tmp_semi);
			return (NULL);
		}
		dlst_pipe = alloc_pipe_list(tmp_semi);
		ft_free2d(tmp_semi);
		tmp_semi = NULL;
		sh->tdlst_pipe = dlst_pipe;
		if (semicolons2d[i + 1])
			sh = process_new_node(sh);
		i++;
	}
	return (sh_head);
}
