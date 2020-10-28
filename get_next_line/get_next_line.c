/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 06:44:13 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/23 19:19:52 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** If any error or mem was not allocated:	return (-1)
** If all went good and EOF:				return (0)
** If all went good and not EOF:			return (1)
*/

#include "get_next_line.h"

char			*g_input;

static _Bool	append_utils(char **append_this, char **remainder, \
								char **line, char **newline_ptr_temp)
{
	char		*temp;

	if (!(*append_this = ft_substr_gnl(*remainder, 0, \
		ft_strlen_gnl(*remainder) - ft_strlen_gnl(*newline_ptr_temp))))
	{
		free(*remainder);
		return (0);
	}
	if (!(temp = ft_strdup_gnl((*newline_ptr_temp) + 1)))
	{
		free(*remainder);
		return (0);
	}
	free(*remainder);
	*remainder = temp;
	temp = NULL;
	if (!(*line = ft_strjoin_gnl(*line, *append_this)))
	{
		free(*append_this);
		return (0);
	}
	free(*append_this);
	*append_this = NULL;
	return (1);
}

static _Bool	append(char **remainder, char **line, _Bool *flag)
{
	char		*newline_ptr_temp;
	char		*append_this;

	if (*remainder)
	{
		if ((newline_ptr_temp = ft_strchr_gnl(*remainder, '\n')))
		{
			if (!(append_utils(&append_this, remainder, \
								line, &newline_ptr_temp)))
				return (0);
			*flag = 0;
		}
		else
		{
			if (!(*line = ft_strjoin_gnl(*line, *remainder)))
			{
				free(*remainder);
				return (0);
			}
			free(*remainder);
			*remainder = NULL;
		}
	}
	return (1);
}

static _Bool	chck_in(int fd, char **line, _Bool *flag, char **remainder)
{
	if (BUFFER_SIZE < 1 || fd < 0)
		return (0);
	if (!(*line = ft_strdup_gnl("")))
		return (0);
	*flag = 1;
	if (*remainder && !(append(remainder, line, flag)))
	{
		free(*remainder);
		free(*line);
		return (0);
	}
	return (1);
}

static _Bool	app_rem(int i, char **remainder, \
								char **newline_ptr, char **line)
{
	char		*temp;

	if (i == -1)
	{
		if (*remainder)
			free(*remainder);
		free(*line);
		return (-1);
	}
	(*newline_ptr)++;
	temp = NULL;
	if (*remainder)
	{
		temp = *remainder;
		*remainder = ft_strjoin_gnl(*remainder, *newline_ptr);
	}
	else
		*remainder = ft_strdup_gnl(*newline_ptr);
	if (temp)
		free(temp);
	temp = NULL;
	if (!(*remainder))
		return (0);
	return (1);
}

int				get_next_line(int fd, char **line, _Bool f, ssize_t bytes_read)
{
	static char	*rem;
	char		buf[BUFFER_SIZE + 1];
	char		*nl_ptr;

	process_g_input();
	if (!line || (read(fd, buf, 0) < 0) || !(chck_in(fd, line, &f, &rem)))
		return (-1);
	while (f && (bytes_read = read(fd, buf, BUFFER_SIZE)) != -1)
	{
		if (bytes_read == 0 && g_input && write_b_b())
			continue ;
		else if (bytes_read == 0)
			return (0);
		if (bytes_read < 0)
			return ((app_rem(-1, &rem, &nl_ptr, line)));
		buf[bytes_read] = 0;
		g_input = ft_strjoin_gnl(g_input, buf);
		if ((nl_ptr = ft_strchr_gnl(buf, '\n')))
		{
			if (!(f = process_nl(nl_ptr)) && !(app_rem(1, &rem, &nl_ptr, line)))
				return (-1);
		}
		*line = ft_strjoin_gnl(*line, buf);
	}
	return ((!f) ? 1 : 0);
}
