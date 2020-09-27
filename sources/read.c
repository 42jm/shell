//read.c////////////////////////////////////////////////////////////////////////

#include "minishell.h"

int	read_userinput(int fd, char **abuf)
{
	ssize_t	ret;
	char	*buf;

	buf = (char *)malloc(sizeof(*buf) * (MAX_INPUT_LENGTH + 1));
	*abuf = buf;
	ret = read(fd, buf, MAX_INPUT_LENGTH);
	if (ret < 0)
	{
		put_error("failed read on input.", NULL);
		free(buf);
		return (1);
	}
	if (ret >= MAX_INPUT_LENGTH)
	{
		put_error("input too long.", NULL);
		free(buf);
		return (2);
	}
	return (0);
}
