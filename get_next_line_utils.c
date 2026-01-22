/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosfy <mosfy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 19:45:00 by mosfy             #+#    #+#             */
/*   Updated: 2026/01/22 19:57:56 by mosfy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	checkbackn(char *s)
{
	size_t	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

static void	copy_join(char *dst, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dst[i] = s2[j];
		i++;
		j++;
	}
	dst[i] = '\0';
}

char	*ft_strjoin_mod(char *s1, char *s2)
{
	char	*res;

	if (!s2)
		return (s1);
	if (!s1)
	{
		s1 = (char *)malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	copy_join(res, s1, s2);
	free(s1);
	return (res);
}

char	*read_loop(int fd, char *save, char *buf)
{
	ssize_t	nbread;

	nbread = 1;
	buf[0] = '\0';
	while (checkbackn(save) && nbread > 0)
	{
		nbread = read(fd, buf, BUFFER_SIZE);
		if (nbread <= 0)
			break;
		buf[nbread] = '\0';
		save = ft_strjoin_mod(save, buf);
		if (!save)
			return (NULL);
	}
	if (nbread < 0)
	{
		free(save);
		return (NULL);
	}
	return (save);
}
