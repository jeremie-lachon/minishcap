#include "minishell.h"

void	subquotefree(void *data)
{
	free(((t_subquote *)data)->str);
	free(data);
}

void	filefree(void *data)
{
	free(((t_file *)data)->filename);
	free(data);
}

void	fdsfree(void *data)
{
	close(((t_fds *)data)->fd);
	free(data);
}
