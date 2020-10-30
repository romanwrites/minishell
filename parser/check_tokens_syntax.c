/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_syntax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:18:07 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/30 16:18:08 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_tokens(t_token *token)
{
	t_token		*ptr;
	int			i;

	i = 0;
	ptr = token;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

static char		**token_to_2d_array(t_token *token, int len)
{
	char		**tokens_2d;
	t_token		*ptr;
	int			i;

	i = 0;
	ptr = token;
	tokens_2d = malloc(sizeof(char *) * (len + 1));
	ft_alloc_check(tokens_2d);
	while (ptr)
	{
		tokens_2d[i++] = ft_strdup_and_check(ptr->content);
		ptr = ptr->next;
	}
	tokens_2d[i] = NULL;
	return (tokens_2d);
}

static _Bool	check_syntax_token(t_token *token)
{
	char		**tokens_2d;

	tokens_2d = token_to_2d_array(token, count_tokens(token));
	if (check_syntax_2d(tokens_2d))
	{
		ft_free2d(tokens_2d);
		return (1);
	}
	ft_free2d(tokens_2d);
	return (0);
}

_Bool			check_tokens_syntax(t_mshell *sv)
{
	while (sv->sh)
	{
		while (sv->sh->tdlst_pipe)
		{
			if (check_syntax_token(sv->sh->tdlst_pipe->token))
				return (1);
			sv->sh->tdlst_pipe->token = sv->sh->tdlst_pipe->token_head;
			sv->sh->tdlst_pipe = sv->sh->tdlst_pipe->next;
		}
		sv->sh->tdlst_pipe = sv->sh->tdlst_pipe_head;
		sv->sh = sv->sh->next;
	}
	sv->sh = sv->sh_head;
	return (0);
}
