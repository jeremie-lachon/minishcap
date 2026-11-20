#include "minishell.h"

t_cmd	*redircmd_out(t_cmd *cmd, char *file, char *efile, int fd)
{
	t_redircmd	*redir;

	redir = ms_calloc(1, sizeof(t_redircmd));
	if (!redir)
		return (NULL);
	redir->type = REDIR;
	redir->cmd = cmd;
	redir->file = ms_filecpy(file, efile);
	if (!redir->file)
		return (free(redir), NULL);
	redir->mode = O_RDONLY;
	redir->fd = fd;
	return ((t_cmd *)redir);
}

t_cmd	*redircmd_in(t_cmd *cmd, char *file, char *efile, int fd)
{
	t_redircmd	*redir;

	redir = ms_calloc(1, sizeof(t_redircmd));
	if (!redir)
		return (NULL);
	redir->type = REDIR;
	redir->cmd = cmd;
	redir->file = ms_filecpy(file, efile);
	if (!redir->file)
		return (free(redir), NULL);
	redir->mode = O_WRONLY | O_CREAT | O_TRUNC;
	redir->fd = fd;
	return ((t_cmd *)redir);
}

t_cmd	*redircmd_append(t_cmd *cmd, char *file, char *efile, int fd)
{
	t_redircmd	*redir;

	redir = ms_calloc(1, sizeof(t_redircmd));
	if (!redir)
		return (NULL);
	redir->type = REDIR;
	redir->cmd = cmd;
	redir->file = ms_filecpy(file, efile);
	if (!redir->file)
		return (free(redir), NULL);
	redir->mode = O_WRONLY | O_CREAT | O_APPEND;
	redir->fd = fd;
	return ((t_cmd *)redir);
}

t_cmd	*redircmd_here(t_herepipe **pipe, t_cmd *cmd)
{
	t_redircmd	*redir;
	t_herepipe	*temp;

	temp = (*pipe)->next;
	redir = ms_calloc(1, sizeof(t_redircmd));
	if (!redir)
		return (NULL);
	redir->type = HERE;
	redir->cmd = cmd;
	redir->mode = O_RDONLY;
	(*pipe)->stored = 1;
	redir->quote = (*pipe)->quote;
	if ((*pipe)->str)
		redir->heredoc = ms_strdup((*pipe)->str);
	if (!redir->heredoc)
		return (free(redir), NULL);
	free((*pipe)->str);
	free(*pipe);
	*pipe = temp;
	return ((t_cmd *)redir);
}
