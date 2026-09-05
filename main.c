#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	int		fd_read;
	int		fd_write;
	char	*line;

	fd_read = open("test.txt", O_RDONLY);
	fd_write = open("cikti.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while ((line = get_next_line(fd_read)))
	{
		write(fd_write, line, ft_strlen(line));
		write(fd_write, "\n", 1); // Her 'a' ile biten parçadan sonra alt satıra geçer
		free(line);
	}
	close(fd_read);
	close(fd_write);
	return (0);
}