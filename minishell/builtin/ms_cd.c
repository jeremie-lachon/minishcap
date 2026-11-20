/*
	cd arg1 arg2    bash: cd: too many arguments
	cd ~ == cd -- == cd $HOME
	cd - == cd $OLDPWD
	cd .. == cd ../
	cd . == cd ./
	cd / == cd // == cd ////////////////////////////
*/

#include "minishell.h"

static int	add_var(char ***env, char *lf, char *to_add)
{
	int	j;

	j = 0;
	while ((*env)[j] != NULL)
	{
		if (!ms_strncmp(lf, (*env)[j], ms_strlen(lf)))
		{
			free((*env)[j]);
			(*env)[j] = ms_strdup(to_add);
			free(to_add);
			if (!(*env)[j])
				return (1);
			break ;
		}
		j++;
	}
	if ((*env)[j] == NULL)
	{
		*env = new_env(env, to_add);
		free(to_add);
		if (!*env)
			return (1);
	}
	return (0);
}

static void	ms_switch_pwd(char *newpwd, char *oldpwd, char ***env)
{
	add_var(env, "OLDPWD=", ms_strjoin("OLDPWD=", oldpwd));
	add_var(env, "PWD=", ms_strjoin("PWD=", newpwd));
}

void	cd_free(char ***str)
{
	if ((*str)[0])
		free((*str)[0]);
	if ((*str)[1])
		free((*str)[1]);
	free(*str);
}

int	ms_cd(t_execs *execs)
{
	char		*oldpwd;
	char		*newpwd;
	int			i;
	t_execcmd	*cmd;

	newpwd = 0;
	cmd = (t_execcmd *)execs->cmd;
	if (cmd->args[1] && cmd->args[2])
		return (ms_printerror("Minishell: cd: too many arguments", 0, 0), 333);
	oldpwd = ms_strdup(get_env_mine("PWD", execs->shell->env));
	if (!oldpwd)
		oldpwd = ms_strdup("");
	i = ms_move(cmd->args, execs->shell->env);
	if (i == 1)
		return (free(oldpwd), 333);
	if (i == 2)
		return (free(oldpwd), execfree(execs), 1);
	ms_getcwd(&newpwd);
	ms_switch_pwd(newpwd, oldpwd, &execs->shell->env);
	if (execs->shell->env == NULL)
		return (free(oldpwd), free(newpwd), 1);
	return (free(oldpwd), free(newpwd), 0);
}

// int main(int ac, char **av, char **env)
// {
//     (void)ac;
//     (void)av;

//     char s[100];

//     char **str = malloc(sizeof(char *) *3);
//     str[0] = strdup("cd");
//     str[1] = strdup("/home/dakojic/code");
//     str[2] = NULL;

//     ms_cd(str, env);

//     return (0);
// }