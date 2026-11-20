#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	line_saver(char *cmd, int *ret)
{
	ms_printerror("minishell: export: `", cmd, "': not a valid identifier");
	*ret = 333;
}

static void	ms_export3(char ***env, int i, char *lf, char **cmd)
{
	int	j;

	j = 0;
	while ((*env)[j] != NULL)
	{
		if (!ms_strncmp(lf, (*env)[j], ms_strlen(lf)))
		{
			free((*env)[j]);
			(*env)[j] = ms_strdup(cmd[i]);
			break ;
		}
		j++;
	}
	if ((*env)[j] == NULL)
		*env = new_env(env, cmd[i]);
}

static int	modded_isalphanum(char *s)
{
	while (*s)
	{
		if ((*s < 'a' || *s > 'z') && (*s < 'A' || *s > 'Z') && (*s < '0'
				|| *s > '9') && *s != '_')
			return (1);
		++s;
	}
	return (0);
}

static void	ms_export2(char **c, char ***env, int i, int *ret)
{
	char	*lf;

	while (!ms_strncmp(c[i +1], "-p", ms_strlen(c[i +1])) && c[i +2] != NULL)
		i++;
	while (c[i++ + 1] != NULL)
	{
		if (!ms_isalpha(c[i][0]) && c[i][0] != '_')
		{
			line_saver(c[i], ret);
			continue ;
		}
		lf = minisplit(c[i], '=');
		if (!lf)
			lf = ms_strdup(c[i]);
		if (modded_isalphanum(lf))
		{
			line_saver(c[i], ret);
			free(lf);
			continue ;
		}
		if (lf == NULL && i++)
			continue ;
		ms_export3(env, i, lf, c);
		free(lf);
	}
}

int	ms_export(t_execs *execs)
{
	int		i;
	char	**args;
	int		ret;

	ret = 0;
	args = ((t_execcmd *)execs->cmd)->args;
	i = 1;
	while (args[i] && (!ms_strncmp(args[i], "-p", 3) && (args[i + 1] != NULL)))
		i++;
	if (args[1] == NULL || (!(ms_strncmp(args[i], "-p", 3)) && args[i
				+ 1] == NULL))
	{
		arrayfree(&args);
		((t_execcmd *)execs->cmd)->args = 0;
		if (ms_write(1, "", 0))
			return (execfree(execs), 1);
		print_env(execs->shell->env);
		return (0);
	}
	ms_export2(args, &(execs->shell->env), 0, &ret);
	arrayfree(&args);
	((t_execcmd *)execs->cmd)->args = 0;
	return (ret);
}
