#include "minishell.h"

static int	ms_execcfree(t_execs *exec)
{
	t_execcmd	*cmd;

	cmd = (t_execcmd *)exec->cmd;
	arrayfree(&cmd->args);
	return (0);
}

static int	ms_solo(t_execs *exec)
{
	t_cmd	*cmd;
	t_cmd	*down;

	cmd = exec->cmd;
	if (cmd->type == HERE)
	{
		free(((t_redircmd *)cmd)->heredoc);
		down = ((t_redircmd *)cmd)->cmd;
	}
	else if (cmd->type == REDIR)
	{
		free(((t_redircmd *)cmd)->file);
		((t_redircmd *)cmd)->file = 0;
		down = ((t_redircmd *)cmd)->cmd;
	}
	else
		down = ((t_sub *)cmd)->cmd;
	ms_sorterfree(exec, down);
	return (0);
}

static int	ms_branch(t_execs *exec)
{
	t_cmd	*cmd;
	t_cmd	*left;
	t_cmd	*right;

	cmd = exec->cmd;
	if (cmd->type == AND)
	{
		left = ((t_andcmd *)cmd)->left;
		right = ((t_andcmd *)cmd)->right;
	}
	else if (cmd->type == OR)
	{
		left = ((t_orcmd *)cmd)->left;
		right = ((t_orcmd *)cmd)->right;
	}
	else
	{
		left = ((t_pipecmd *)cmd)->left;
		right = ((t_pipecmd *)cmd)->right;
	}
	ms_sorterfree(exec, left);
	ms_sorterfree(exec, right);
	return (0);
}

int	ms_sorterfree(t_execs *exec, t_cmd *cmd)
{
	exec->cmd = cmd;
	if (!cmd)
		return (free(cmd), 0);
	if (cmd->type == EXEC)
		ms_execcfree(exec);
	else if (cmd->type == SUB || cmd->type == REDIR || cmd->type == HERE)
		ms_solo(exec);
	else if (cmd->type == PIPE || cmd->type == AND || cmd->type == OR)
		ms_branch(exec);
	free(cmd);
	return (0);
}
