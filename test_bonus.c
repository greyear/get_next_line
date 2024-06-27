#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

//в системе у текстовых файлов нет дескрипторов на жестком диске, пока мы не вызвали команду опен! нужно ли нам написать ограничение до 1023 или просто на несуществующий дескриптор?


int	main(void)
{
	int			fd[3];
	char		*next_line;
	int			count;

	fd[0] = open("lolita.txt", O_RDONLY);
	fd[1] = open("bible.txt", O_RDONLY);
	//fd = open("empty.txt", O_RDONLY);
	//fd = open("nl.txt", O_RDONLY);
	//fd = open("nls.txt", O_RDONLY);
	//fd = open("letter.txt", O_RDONLY);
	fd[2] = open("someonescode.txt", O_RDONLY);
	count = 0;
	while (1)
	{
		next_line = get_next_line(fd[0]);
		if (next_line == NULL)
			break ;
		count++;
		printf("%d:%s\n", count, next_line);
		
		next_line = get_next_line(fd[1]);
		if (next_line == NULL)
			break ;
		count++;
		printf("%d:%s\n", count, next_line);
		
		next_line = get_next_line(fd[2]);
		if (next_line == NULL)
			break ;
		count++;
		printf("%d:%s\n", count, next_line);

		next_line = NULL;
	}
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	return (0);
}

