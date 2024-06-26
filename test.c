#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

//в системе у текстовых файлов нет дескрипторов на жестком диске, пока мы не вызвали команду опен! нужно ли нам написать ограничение до 1023 или просто на несуществующий дескриптор?


int	main(void)
{
	int			fd;
	char		*next_line;
	int			count;
	int			bytes;

	fd = open("lolita.txt", O_RDONLY);
	//fd = open("empty.txt", O_RDONLY);
	//fd = open("nl3.txt", O_RDONLY);
	//fd = open("nls.txt", O_RDONLY);
	//fd = open("letter.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	count = 0;
	while (1)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		count++;
		printf("%d:%s\n", count, next_line);
		next_line = NULL;
	}
	close(fd);
	return (0);
}

