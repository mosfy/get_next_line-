/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosfy <mosfy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:23:27 by tfrances          #+#    #+#             */
/*   Updated: 2025/12/02 18:13:02 by mosfy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	checkbackn(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strjoin_mod(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*r;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	r = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!r)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		r[i++] = s2[j++];
	r[i] = '\0';
	free(s1);
	return (r);
}

char	*extractline(char *save)
{
	int		i;
	char	*line;

	if (!save || save[0] == '\0')
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc(i + (save[i] == '\n') + 1);
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

char	*cleansave(char *save)
{
	int		i;
	int		j;
	char	*sret;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	i++;
	sret = malloc(ft_strlen(save) - i + 1);
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

char *get_next_line(int fd)
{
    static char *save;
    char tmp[BUFFER_SIZE + 1];
    int nbread;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    nbread = 1;
    while (checkbackn(save) && nbread > 0)
    {
        nbread = read(fd, tmp, BUFFER_SIZE);
        if (nbread < 0)
        {
            free(save);
            save = NULL;
            return (NULL);  // Handle read error
        }

        if (nbread == 0)  // End of file
            break;

        tmp[nbread] = '\0';
        save = ft_strjoin_mod(save, tmp);
        if (!save)
            return (NULL);  // Return NULL if memory allocation fails
    }

    line = extractline(save);  // Extract line from save buffer
    if (!line)
        return (NULL);  // Return NULL if no line found

    save = cleansave(save);  // Clean up static buffer
    return (line);
}


// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("mon_fichier.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
