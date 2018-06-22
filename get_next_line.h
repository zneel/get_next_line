#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define BUFF_SIZE 4096

int	get_next_line(const int fd, char **line);

#endif