#include "get_next_line.h"


char	*ft_strnew(size_t size)
{
	char *s;

	s = (char*)malloc(sizeof(*s) * (size + 1));
	if (!s)
		return (NULL);
	memset(s, 0, size + 1);
	return (s);
}

char	*ft_strjfree(char *s1, const char *s2)
{
	size_t	count;
	size_t	len[2];
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len[0] = strlen(s1);
	len[1] = strlen(s2);
	str = ft_strnew(len[0] + len[1]);
	if (str == NULL)
		return (NULL);
	count = 0;
	while (count < len[0])
	{
		str[count] = s1[count];
		count++;
	}
	while (count < (len[0] + len[1]))
	{
		str[count] = s2[count - len[0]];
		count++;
	}
	str[count] = '\0';
	free(s1);
	return (str);
}

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
	str = strdup(s);
	free(l);
	return (str);
}

static char	**tokenline(char **line, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\n')
		i++;
	*line = strndup(str, i);
	return (line);
}

static char	*buffertostr(char *str, char *buff, ssize_t bytes)
{
	if (!str)
		str = strdup(buff);
	else if (bytes != 0 && str && strchr(str, '\n') == 0)
		str = ft_strjfree(str, buff);
	return (str);
}

static int readline(char **stc, char **line, int fd, ssize_t bytes)
{
	if (bytes == 0 && *stc[fd] == '\0')
		return (0);
	else if (bytes == 0 && strchr(stc[fd], '\n') == 0)
	{
		*line = strdup(stc[fd]);
		bzero(stc[fd], strlen(stc[fd]));
		return (1);
	}
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	ssize_t		bytes;
	static char	*stc[FOPEN_MAX];

	if (fd < 0 || !line)
		return (-1);
	bytes = 1;
	while (bytes != 0)
	{
		if (!stc[fd] || strchr(stc[fd], '\n') == 0)
		{
			bytes = read(fd, buff, BUFF_SIZE);
			buff[bytes] = '\0';
		}
		if (bytes == 0)
			return (readline(stc, line, fd, bytes));
		stc[fd] = buffertostr(stc[fd], buff, bytes);
		if ((strchr(stc[fd], '\n')) != 0)
		{
			line = tokenline(line, stc[fd]);
			stc[fd] = tokenstr(stc[fd]);
			return (1);
		}
	}
}