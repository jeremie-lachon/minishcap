#include "minishell.h"

int	ms_write(int fd, char *str, int size)
{
	int	err;

	err = write(fd, str, size);
	if (err == -1 && errno != EPIPE)
	{
		perror("minishell: write error ");
		return (1);
	}
	else if (err == -1 && errno == EPIPE)
		return (1);
	return (0);
}
