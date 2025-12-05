/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosfy <mosfy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 19:45:00 by mosfy             #+#    #+#             */
/*   Updated: 2025/12/05 19:21:32 by mosfy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extractline(char *save)
{
	size_t	i;
	char	*line;

	if (!save || save[0] == '\0')
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	line = (char *)malloc(i + (save[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static size_t	nl_pos(char *save)
{
	size_t	i;

	if (!save)
		return ((size_t) - 1);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
		return ((size_t) - 1);
	return (i + 1);
}

static char	*cleansave(char *save)
{
	size_t	i;
	size_t	j;
	char	*sret;

	i = nl_pos(save);
	if (i == (size_t)-1)
	{
		free(save);
		return (NULL);
	}
	sret = (char *)malloc(ft_strlen(save) - i + 1);
	if (!sret)
	{
		free(save);
		return (NULL);
	}
	j = 0;
	while (save[i])
		sret[j++] = save[i++];
	sret[j] = '\0';
	free(save);
	return (sret);
}

static char	*read_to_save(int fd, char *save)
{
	char	*buf;
	char	*res;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
	{
		free(save);
		return (NULL);
	}
	res = read_loop(fd, save, buf);
	free(buf);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = read_to_save(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = extractline(save[fd]);
	if (!line)
	{
		free(save[fd]);
		save[fd] = NULL;
		return (NULL);
	}
	save[fd] = cleansave(save[fd]);
	return (line);
}
