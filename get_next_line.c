/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 14:33:59 by ebouvier          #+#    #+#             */
/*   Updated: 2018/07/06 13:17:46 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*tokenstr(char *str)
{
	int		i;
	char	*s;
	char	*l;

	i = 0;
	while (str[i] != '\n')
		i++;
	s = &str[i + 1];
	l = str;
	str = ft_strdup(s);
	free(l);
	return (str);
}

static char	**tokenline(char **line, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\n')
		i++;
	*line = ft_strndup(str, i);
	return (line);
}

static char	*buffertostr(char *str, char *buff, ssize_t bytes)
{
	if (!str)
		str = ft_strdup(buff);
	else if (bytes != 0 && str && ft_strchr(str, '\n') == 0)
		str = ft_strjfree(str, buff);
	return (str);
}

static int	readline(char **stc, char **line, int fd, ssize_t bytes)
{
	if (bytes == 0 && *stc[fd] == '\0')
		return (0);
	else if (bytes == 0 && ft_strchr(stc[fd], '\n') == 0)
	{
		*line = ft_strdup(stc[fd]);
		ft_bzero(stc[fd], ft_strlen(stc[fd]));
		return (1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	ssize_t		bytes;
	static char	*stc[OPEN_MAX];

	if (fd < 0 || !line || read(fd, buff, 0) < 0)
		return (-1);
	bytes = 1;
	while (bytes != 0)
	{
		if (!stc[fd] || ft_strchr(stc[fd], '\n') == 0)
		{
			bytes = read(fd, buff, BUFF_SIZE);
			buff[bytes] = '\0';
		}
		if ((stc[fd] = buffertostr(stc[fd], buff, bytes)) != NULL
				&& (ft_strchr(stc[fd], '\n') != 0))
		{
			line = tokenline(line, stc[fd]);
			stc[fd] = tokenstr(stc[fd]);
			return (1);
		}
	}
	return (readline(stc, line, fd, bytes));
}
