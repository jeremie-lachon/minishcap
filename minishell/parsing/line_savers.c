#include "minishell.h"

void	saver(int in)
{
	signals();
	dup2(in, 0);
	close(in);
}

void	saver2(int *in, char **buf)
{
	*in = dup(0);
	signals_heredoc();
	*buf = ms_calloc(1, sizeof(char));
}
