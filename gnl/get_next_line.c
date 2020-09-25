/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 18:34:24 by lhelper           #+#    #+#             */
/*   Updated: 2020/05/24 18:34:24 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int		new_line(char **line, char **file_des_arr, char *ptr)
{
	char *swap;

	*line = ft_strdup(*file_des_arr);
	if (*line == NULL)
		return (-1);
	if (*ptr != '\0')
	{
		swap = ft_strdup(ptr);
		free(*file_des_arr);
		if (swap == NULL)
			return (-1);
		*file_des_arr = swap;
	}
	else
	{
		free(*file_des_arr);
		*file_des_arr = NULL;
	}
	return (1);
}

static	int		tail(char **line, char **file_des_arr, char *ptr, int i)
{
	if (i == -1)
		return (-1);
	if (*file_des_arr != NULL && (ptr = ft_strchr(*file_des_arr, '\n')))
	{
		*ptr = '\0';
		ptr++;
		return (new_line(line, file_des_arr, ptr));
	}
	if (*file_des_arr != NULL)
	{
		*line = *file_des_arr;
		*file_des_arr = NULL;
		return (0);
	}
	*line = ft_strdup("");
	if (*line == NULL)
		return (-1);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	int			i;
	char		*ptr;
	char		buf[BUFFER_SIZE + 1];
	static char	*file_des_arr[1024];

	if ((read(fd, buf, 0) < 0) || fd > 1023 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	ft_bzero(buf, BUFFER_SIZE + 1);
	while ((i = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		ptr = ft_strjoin(file_des_arr[fd], buf);
		free(file_des_arr[fd]);
		file_des_arr[fd] = ptr;
		if (file_des_arr[fd] == NULL)
			return (-1);
		ft_bzero(buf, BUFFER_SIZE + 1);
		if ((ptr = ft_strchr(file_des_arr[fd], '\n')))
		{
			*ptr++ = '\0';
			return (new_line(line, &file_des_arr[fd], ptr));
		}
	}
	if (file_des_arr[fd] != NULL)
		ptr = ft_strchr(file_des_arr[fd], '\n');
	return (tail(line, &file_des_arr[fd], ptr, i));
}
