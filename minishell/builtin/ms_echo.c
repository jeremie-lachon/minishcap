#include "minishell.h"

// Takes pointer to execcmd struct as arg since its the end product and frees it
// Echo always returns 0 unless write fails

static int	n_option(char **cmd, int *i, bool *arg)
{
	int	j;

	j = 2;
	while (cmd[*i] && cmd[*i][0] == '-' && cmd[*i][1] == 'n')
	{
		while (cmd[*i][j] == 'n')
			j++;
		if (cmd[*i][j] == '\0')
			*arg = true;
		else
			return (0);
		(*i)++;
		j = 2;
	}
	return (0);
}

int	ms_echo(t_execs *execs)
{
	int			i;
	bool		n_arg;
	t_execcmd	*cmd;

	if (ms_write(1, "", 0))
		return (333);
	cmd = (t_execcmd *)execs->cmd;
	i = 1;
	n_arg = false;
	n_option(cmd->args, &i, &n_arg);
	while (cmd->args[i])
	{
		write(1, cmd->args[i], ms_strlen(cmd->args[i]));
		if (cmd->args[i + 1] != 0)
			ms_write(1, " ", 1);
		i++;
	}
	if (n_arg == false || (cmd->args[1] && !cmd->args[2] && !cmd->args[1][0]))
		ms_write(1, "\n", 1);
	i = 0;
	arrayfree(&cmd->args);
	cmd->args = 0;
	return (0);
}

// int main()
// {
//     char **cmd = malloc(5 * sizeof(char *));
//     if (!cmd) return (1);

//     cmd[0] = strdup("echo");
	// Use strdup to duplicate string literals safely
//     cmd[1] = strdup("-nABCn");
//     cmd[2] = strdup("-n");
//     cmd[3] = strdup("World");
//     cmd[4] = NULL;
//     ms_echo(&cmd);
//     // ms_echo(&cmd);
//     return (0);
// }