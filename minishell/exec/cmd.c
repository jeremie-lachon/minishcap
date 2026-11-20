#include "minishell.h"

int	ms_sorter(t_execs *exec, t_cmd *cmd)
{
	int	err;

	exec->cmd = cmd;
	err = 0;
	if (g_bigsignal == SIGINT)
		return (exec->ret);
	if (!cmd)
		exec->ret = err;
	else if (cmd->type == EXEC)
		err = ms_exec(exec, 0, (t_execcmd *)cmd);
	else if (cmd->type == PIPE)
		err = ms_pipe(exec, 0, (t_pipecmd *)cmd);
	else if (cmd->type == REDIR)
		err = ms_redir(exec, 0, (t_redircmd *)cmd);
	else if (cmd->type == AND)
		err = ms_and(exec, 0, (t_andcmd *)cmd);
	else if (cmd->type == OR)
		err = ms_or(exec, 0, (t_orcmd *)cmd);
	else if (cmd->type == HERE)
		err = ms_here(exec, 0, (t_redircmd *)cmd);
	else
		err = ms_sub(exec, 0, (t_sub *)cmd);
	if (cmd && err != 1)
		exec->ret = err;
	return (err);
}

int	ms_exec3(int err)
{
	if (WIFSIGNALED(err) && WTERMSIG(err) == SIGINT)
		g_bigsignal = SIGINT;
	if (WIFEXITED(err))
		err = WEXITSTATUS(err);
	if (err == 1)
		err = 333;
	return (err);
}

static int	ms_exec2(t_execs *exec, char **args, int err, t_execcmd *cmds)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		if (ms_setfds(exec))
			exit_execfree(exec, 333);
		ms_closeallfds(exec);
		if (!args[0])
			exit_execfree(exec, 0);
		err = ms_command(exec, cmds, 0);
		if (!err)
		{
			signal(SIGQUIT, SIG_DFL);
			execve(args[0], args, exec->shell->env);
			signal(SIGQUIT, SIG_IGN);
		}
		exit_execfree(exec, err);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &err, 0);
	err = ms_exec3(err);
	if (err == 131 && g_bigsignal != SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
	return (err);
}

int	ms_exec(t_execs *exec, int err, t_execcmd *cmds)
{
	char		**args;

	if (!exec->cmd || !((t_execcmd *)exec->cmd)->args)
		return (0);
	args = cmds->args;
	if (!isbuiltin(args[0]))
		err = ms_exec2(exec, args, err, cmds);
	else
		err = builtin(exec);
	if (g_bigsignal == SIGINT)
		err = 130;
	return (signals(), err);
}
