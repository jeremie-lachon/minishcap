#include "minishell.h"

t_subquote	*subquotenew(char *data, int check)
{
	t_subquote	*new;

	new = ms_calloc(sizeof(t_subquote), 1);
	if (!new)
		return (free(data), NULL);
	new->check = check;
	new->str = data;
	return (new);
}

t_file	*filenew(char *data)
{
	t_file	*new;

	new = ms_calloc(sizeof(t_file), 1);
	if (!new)
		return (free(data), NULL);
	new->filename = data;
	return (new);
}

t_fds	*fdsnew(int fd, int type)
{
	t_fds	*new;

	new = ms_calloc(sizeof(t_fds), 1);
	if (!new)
		return (close(fd), NULL);
	new->fd = fd;
	new->type = type;
	return (new);
}
