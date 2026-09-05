#include "get_next_line.h"

static char	*read_file(int fd, char *str)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(str),NULL);
	bytes = 1;
	while (!ft_strchr(str, 'a') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buffer),free(str),NULL);
		buffer[bytes] = '\0';
		temp = str;
		str = ft_strjoin(temp, buffer);
		free(temp);
	}
	free(buffer);
	return (str);
}

static char	*make_line(char *str)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!str || !str[0])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*clean_str(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	i++;
	new_str = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	j = 0;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = read_file(fd, str);
	if (!str)
		return (NULL);
	line = make_line(str);
	str = clean_str(str);
	return (line);
}