#include "get_next_line.h"

int main(int argc, char **argv)
{
	char	*str;
	int		fd;

	if (argc < 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &str) > 0)
	{
		printf("%s\n", str);
		free(str);
	}
	close(fd);
	return (0);
}