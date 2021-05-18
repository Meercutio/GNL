#include "get_next_line.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (size--)
		str[size] = '\0';
	return (str);
}

char	*check_rem(char *rem, char **line)
{
	char	*ptr_n;

	ptr_n = NULL;
	if (rem)
	{
		ptr_n = ft_strchr(rem, '\n');
		if (ptr_n)
		{
			*ptr_n = '\0';
			ptr_n++;
			*line = ft_strdup(rem);
			ft_strlcpy(rem, ptr_n, ft_strlen(ptr_n + 1));
		}
		else
		{
			*line = ft_strdup(rem);
			free(rem);
		}
	}
	else
		*line = ft_strnew(0);
	return (ptr_n);
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			byte_wr;
	char		*ptr_n;
	static char	*rem;
	char		*tmp;

	if (fd < 0 || fd > 19 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	ptr_n = check_rem(rem, line);
	byte_wr = read(fd, buf, BUFFER_SIZE);
	while (!ptr_n && byte_wr)
	{
		buf[byte_wr] = '\0';
		ptr_n = ft_strchr(buf, '\n');
		if (ptr_n)
		{
			*ptr_n = '\0';
			ptr_n++;
			rem = ft_strdup(ptr_n);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
		byte_wr = read(fd, buf, BUFFER_SIZE);
	}
	if (byte_wr || ft_strlen(rem) || ft_strlen(*line))
		return (1);
	else
		return (0);
}
