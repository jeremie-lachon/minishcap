#include "minishell.h"

int	isbuiltin(char *cmd)
{
	if (!ms_strncmp(cmd, "echo", 5))
		return (1);
	if (!ms_strncmp(cmd, "cd", 3))
		return (2);
	if (!ms_strncmp(cmd, "pwd", 4))
		return (3);
	if (!ms_strncmp(cmd, "export", 7))
		return (4);
	if (!ms_strncmp(cmd, "unset", 6))
		return (5);
	if (!ms_strncmp(cmd, "env", 4))
		return (6);
	if (!ms_strncmp(cmd, "exit", 5))
		return (7);
	return (0);
}

int	builtin(t_execs *exec)
{
	int	command;
	int	err;

	signal(SIGPIPE, SIG_IGN);
	ms_setfds(exec);
	command = isbuiltin(((t_execcmd *)exec->cmd)->args[0]);
	if (command == 1)
		err = ms_echo(exec);
	else if (command == 2)
		err = ms_cd(exec);
	else if (command == 3)
		err = ms_pwd(exec);
	else if (command == 4)
		err = ms_export(exec);
	else if (command == 5)
		err = ms_unset(exec);
	else if (command == 6)
		err = ms_env(exec);
	else
		err = ms_exit(exec);
	if (err != 1 && dup2(exec->stdcopies[0], 0) != -1
		&& dup2(exec->stdcopies[1], 1) != -1)
		return (signal(SIGPIPE, SIG_DFL), err);
	return (signal(SIGPIPE, SIG_DFL), err);
}

char	**new_env(char ***env, char *cmd)
{
	char	**new;
	int		i;

	i = 0;
	while ((*env)[i] != NULL)
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*env)[i] != NULL)
	{
		new[i] = ms_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	new[i] = ms_strdup(cmd);
	new[i + 1] = NULL;
	free(*env);
	return (new);
}

char	*minisplit(char *s, int c)
{
	char	*new;
	int		i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == '\0')
		return (NULL);
	new = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] != c)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
