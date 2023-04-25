/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakshmi <alakshmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:06:27 by alakshmi          #+#    #+#             */
/*   Updated: 2023/03/10 22:48:56 by alakshmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*readline(int fd, char *bufferstr)
{
	char	*line;
	int		readbytes;

	line = malloc(sizeof(char) * ((unsigned int)BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	readbytes = -1;
	while (!ft_strchr(bufferstr, '\n') && readbytes != 0)
	{
		readbytes = read(fd, line, BUFFER_SIZE);
		if (readbytes == -1)
		{
			free(line);
			return (NULL);
		}
		line[readbytes] = '\0';
		bufferstr = ft_strjoin(bufferstr, line);
	}
	free(line);
	return (bufferstr);
}

char	*remline(char *bufferstr)
{
	int		i;
	char	*line;

	i = 0;
	if (!bufferstr[i])
		return (NULL);
	while (bufferstr[i] && bufferstr[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (bufferstr[i] && (bufferstr[i] != '\n'))
	{
		line[i] = bufferstr[i];
		i++;
	}
	if (bufferstr[i] == '\n')
	{
		line[i] = bufferstr[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*trimbuffer(char *bufferstr)
{
	char	*line;
	int		i;
	int		nlindx;

	nlindx = 0;
	while (bufferstr[nlindx] && bufferstr[nlindx] != '\n')
		nlindx++;
	if (!bufferstr[nlindx])
		return (free(bufferstr), NULL);
	++nlindx;
	line = (char *)malloc(sizeof(char) * (ft_strlen(bufferstr) - nlindx + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (bufferstr[nlindx])
		line[i++] = bufferstr[nlindx++];
	line[i] = '\0';
	free(bufferstr);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*bufferstr;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (0);
	bufferstr = readline(fd, bufferstr);
	if (!bufferstr)
		return (NULL);
	line = remline(bufferstr);
	bufferstr = trimbuffer(bufferstr);
	return (line);
}
