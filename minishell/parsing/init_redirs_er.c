#include "minishell.h"

t_cmd	*redircmd_in2(t_cmd *cmd, char *file, char *efile, int fd)
{
	t_redircmd	*redir;

	redir = ms_calloc(1, sizeof(t_redircmd));
	if (!redir)
		return (NULL);
	redir->type = REDIR;
	redir->file = ms_filecpy(file, efile);
	if (!redir->file)
		return (free(redir), NULL);
	redir->mode = O_WRONLY | O_CREAT | O_TRUNC;
	redir->fd = fd;
	redir->cmd = ((t_redircmd *)cmd)->cmd;
	((t_redircmd *)cmd)->cmd = (t_cmd *)redir;
	return ((t_cmd *)redir);
}

t_cmd	*redircmd_out2(t_cmd *cmd, char *file, char *efile, int fd)
{
	t_redircmd	*redir;

	redir = ms_calloc(1, sizeof(t_redircmd));
	if (!redir)
		return (NULL);
	redir->type = REDIR;
	redir->file = ms_filecpy(file, efile);
	if (!redir->file)
		return (free(redir), NULL);
	redir->mode = O_RDONLY;
	redir->fd = fd;
	redir->cmd = ((t_redircmd *)cmd)->cmd;
	((t_redircmd *)cmd)->cmd = (t_cmd *)redir;
	return ((t_cmd *)redir);
}

t_cmd	*redircmd_append2(t_cmd *cmd, char *file, char *efile, int fd)
{
	t_redircmd	*redir;

	redir = ms_calloc(1, sizeof(t_redircmd));
	if (!redir)
		return (NULL);
	redir->type = REDIR;
	redir->file = file;
	redir->file = ms_filecpy(file, efile);
	if (!redir->file)
		return (free(redir), NULL);
	redir->mode = O_WRONLY | O_CREAT | O_APPEND;
	redir->fd = fd;
	redir->cmd = ((t_redircmd *)cmd)->cmd;
	((t_redircmd *)cmd)->cmd = (t_cmd *)redir;
	return ((t_cmd *)redir);
}

t_cmd	*redircmd_here2(t_herepipe **pipe, t_cmd *cmd)
{
	t_redircmd	*redir;
	t_herepipe	*temp;

	temp = (*pipe)->next;
	redir = ms_calloc(1, sizeof(t_redircmd));
	if (!redir)
		return (NULL);
	redir->type = HERE;
	redir->cmd = cmd;
	redir->file = NULL;
	redir->efile = NULL;
	redir->mode = O_RDONLY;
	redir->fd = 0;
	(*pipe)->stored = 1;
	redir->quote = (*pipe)->quote;
	if ((*pipe)->str)
		redir->heredoc = ms_strdup((*pipe)->str);
	if (!redir->heredoc)
		return (free(redir), NULL);
	free((*pipe)->str);
	free(*pipe);
	*pipe = temp;
	redir->cmd = ((t_redircmd *)cmd)->cmd;
	((t_redircmd *)cmd)->cmd = (t_cmd *)redir;
	return ((t_cmd *)redir);
}
