/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:22:57 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/20 16:22:58 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		set_token_flag(t_token *token, char *str)
{
	if (((str[0] == REDIR_RIGHT || str[0] == REDIR_LEFT) && \
		!str[1]) || !(ft_strcmp(str, REDIR_RIGHT_DOUBLE)))
	{
		token->is_diff = 1;
	}
	else
		token->is_diff = 0;
}

static void		init_t_open_q(t_open_q *o, const char *str)
{
	o->new_line = ft_strdup_and_check("");
	o->save = 0;
	o->append_this = NULL;
	o->str = ft_strdup_and_check(str);
}

static void		free_o(t_open_q *o)
{
	free(o->str);
	o->str = NULL;
	o->new_line = NULL;
}

void			open_quotes(t_token *token)
{
	char		*tmp;
	t_open_q	*o;
	static char	tab_[] = {DOLLAR, DOUBLE_QUOTE, BACKSLASH, GRAVE_ACCENT, '\0'};

	o = malloc(sizeof(t_open_q));
	ft_alloc_check(o);
	o->tab = tab_;
	tmp = NULL;
	while (token)
	{
		init_globs();
		set_token_flag(token, token->content);
		if (token->is_diff)
		{
			token = token->next;
			continue ;
		}
		init_t_open_q(o, token->content);
		tmp = token->content;
		token->content = open_quotes_str(o, 0);
		free(tmp);
		free_o(o);
		token = token->next;
	}
	free(o);
}
