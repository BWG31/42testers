#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int		fd;
	char	*line;

	fd = open("test_text.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("\n	=== First read ===\n");
	if (!line)
		printf("Error1\n");
	else
		printf("%s", line);
	free(line);


	line = get_next_line(fd);
	printf("\n	=== Second read ===\n");
	if (!line)
		printf("Error2\n");
	else
		printf("%s", line);
	free(line);
	
	
	line = get_next_line(fd);
	printf("\n	=== Third read ===\n");
	if (!line)
		printf("Error3\n");
	else
		printf("%s", line);
	free(line);


	line = get_next_line(fd);
	printf("\n	=== Fourth read ===\n");
	if (!line)
		printf("Error4\n");
	else
		printf("%s", line);
	free(line);


	close(fd);
	return (0);
}

