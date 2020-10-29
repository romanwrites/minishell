/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romankukin <romankukin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 06:44:21 by mkristie          #+#    #+#             */
/*   Updated: 2020/07/05 19:02:24 by romankukin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char		*ft_strdup_gnl(const char *s1)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = ft_strlen_gnl(s1);
	i = 0;
	str = malloc(len + 1);
	ft_alloc_check(str);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char		*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if (ft_strlen_gnl(s) < start)
		return (ft_strdup_gnl(""));
	if (len > ft_strlen_gnl(s) - start)
		len = ft_strlen_gnl(s) - start;
	if (!(str = malloc(len + 1)))
		return (NULL);
	while (i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

char		*ft_strchr_gnl(const char *s, int c)
{
	int		i;

	i = 0;
	if ((char)c == '\0')
		return ((void *)s + ft_strlen_gnl(s));
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}

char		*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	len;
	char	*save;
	char	*s1_holder;

	len = 0;
	s1_holder = s1;
	if (!s1 && s2)
		len = ft_strlen_gnl(s2) + 1;
	else if (s1 && s2)
		len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1;
	str = malloc(sizeof(*str) * (len));
	ft_alloc_check(str);
	save = str;
	if (s1)
		while (*s1)
			*str++ = *s1++;
	if (s2)
		while (*s2)
			*str++ = *s2++;
	*str = 0;
	free(s1_holder);
	return (save);
}
