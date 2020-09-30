/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 00:47:50 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/30 00:47:59 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool		find_next_double_q_mark(t_mshell *sv, char c, int j)
{
	while (sv->content[j])
	{
		if ((c == 34 && sv->content[j] == 34 && sv->content[j - 1] != 92) \
			|| (c == 39 && sv->content[j] == 39))
		{
			sv->i = j + 1;
			return (1);
		}
		j++;
	}
	return (0);
}

int			count_tokens(t_mshell *sv)
{
	sv->i = 0;
	_Bool	double_quote_flag = 0;
	_Bool	single_quote_flag = 0;
	int		tokens = 0;

	while (sv->content[sv->i])
	{
		if (sv->content[sv->i] == 34 && sv->content[sv->i - 1] != 92 && !double_quote_flag)
		{
			double_quote_flag = 1;
			tokens += 1;
			sv->i++;
			if (find_next_double_q_mark(sv, sv->content[sv->i - 1], sv->i))
			{
				tokens += 1;
				double_quote_flag = 0;
				continue ;
			}
			exit_error_message("Error!\nfunction: count_tokens\nmessage: [Double Quotes are open]");
		}
		if (sv->content[sv->i] == 39 && !single_quote_flag)
		{
			single_quote_flag = 1;
			tokens += 1;
			sv->i++;
			if (find_next_double_q_mark(sv, sv->content[sv->i - 1], sv->i))
			{
				tokens += 1;
				single_quote_flag = 0;
				continue ;
			}
			exit_error_message("Error!\nfunction: count_tokens\nmessage: [Single Quotes are open]");
		}
		sv->i++;
	}
	if (!tokens && sv->content[0])
		tokens++;
	return (tokens);
}


void		alloc_token_str(t_mshell *sv, char **str, int start, int finish)
{
	char 	*tmp;
	char 	*new_line;

	tmp = ft_calloc(finish - start + 1, 1);
	ft_alloc_check(tmp);

	new_line = tmp;
	while (start < finish)
	{
		*tmp++ = sv->content[start++];
	}
	*tmp = 0;
	*(str) = new_line;
}

void		alloc_token_quotes(t_mshell *sv, char **str, int *pos)
{
	int		j = *pos;

	if ((sv->content[j] == 34 && (j == 0 || sv->content[j - 1] != 92)) \
		|| sv->content[*pos] == 39)
	{
		j++;
		if (find_next_double_q_mark(sv, sv->content[j - 1], j))
		{
			alloc_token_str(sv, str, *pos, sv->i);
			*pos = sv->i;
			return ;
		}
	}
	else
	{
		while (sv->content[j] && !((sv->content[j] == 34 && sv->content[j - 1] != 92) \
				|| (sv->content[j] == 39)))
			j++;
		alloc_token_str(sv, str, *pos, j);
		*pos = j;
		return ;
	}
	exit_error_message("ERROR alloc_token_quotes()"); // don't go here
}

char		**split_by_quotes(t_mshell *sv)
{
	int		tokens = count_tokens(sv);
	int		j = 0;
	char	**quotes_2d = (char **)ft_calloc(tokens + 1, sizeof(char *));
	ft_alloc_check(quotes_2d);

	int		*pos = malloc(sizeof(int));
	ft_alloc_check(pos);

	*pos = 0;
	while (j < tokens)
	{
		alloc_token_quotes(sv, &(quotes_2d[j]), pos);
		j++;
	}
	quotes_2d[j] = NULL;
	free(pos);
	return (quotes_2d);
}