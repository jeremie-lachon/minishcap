#include "minishell.h"

int	ms_and(t_execs *exec, int err, t_andcmd *cmds)
{
	if (!exec->cmd)
		return (0);
	if (ms_expandcmd(exec, cmds->left))
		return (execfree(exec), 1);
	err = ms_sorter(exec, cmds->left);
	if (!err)
	{
		if (ms_expandcmd(exec, cmds->right))
			return (execfree(exec), 1);
		err = ms_sorter(exec, cmds->right);
	}
	return (err);
}

int	ms_or(t_execs *exec, int err, t_orcmd *cmds)
{
	if (!exec->cmd)
		return (0);
	if (ms_expandcmd(exec, cmds->left))
		return (execfree(exec), 1);
	err = ms_sorter(exec, cmds->left);
	if (err != 0 && err != 1)
	{
		if (ms_expandcmd(exec, cmds->right))
			return (execfree(exec), 1);
		err = ms_sorter(exec, cmds->right);
	}
	return (err);
}

static void	ms_sub2(t_execs *exec, t_shell *shell, char *buff, t_sub *cmds)
{
	int	err;

	if (ms_expandcmd(exec, cmds->cmd))
		exit_execfree(exec, 1);
	err = ms_sorter(exec, cmds->cmd);
	if (err != 1)
		execfree(exec);
	arrayfree(&shell->env);
	free(buff);
	free(shell);
	exit(err);
}

int	ms_sub(t_execs *exec, int err, t_sub *cmds)
{
	int	pid;

	if (!exec->cmd)
		return (0);
	pid = fork();
	if (!pid)
		ms_sub2(exec, exec->shell, exec->buff, cmds);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &err, 0);
		signals();
	}
	if (err == 1)
		err = 333;
	return (err);
}
