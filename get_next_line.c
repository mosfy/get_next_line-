/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfrances <tfrances@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:23:27 by tfrances          #+#    #+#             */
/*   Updated: 2025/11/29 16:41:40 by tfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlenline(int fd)
{
	int	i;
	char *tmp;

	i = 0;
	while (read (fd,tmp,1))
	{
		i++;
		if (tmp[0] == '\n')
			return(i);
	}
	return (i);
}

char *get_next_line(int fd)
{
	static char*	tmp;
	char*			sret;
	int				i;
	int				j;

	i = 0;
	j = 0;
	tmp = malloc(BUFFER_SIZE + 1);
	sret = malloc(ft_strlenline(fd));
	while (read (fd,tmp,BUFFER_SIZE))
	{
		while (tmp[i] && tmp[i] != '\n')
		{
			sret[j] = tmp[i];
			i++;
		}
		if(tmp[i] == '\n')
		{
			sret[j] = '\n';
			return (sret);
		}
	}
}

int main() 
{
	int fd;
	char *line;

	fd = open("mon_fichier.txt", O_RDONLY);
	if (fd == -1) {
		return 1;
	}

	while ((line = get_next_line(fd)) != NULL) 
	{
		printf("%s", line);
		free(line);
	}
	close(fd);

	return 0;
}
