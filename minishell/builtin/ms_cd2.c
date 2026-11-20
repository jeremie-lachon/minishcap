#include "minishell.h"

char	*get_env_mine(char *name, char **env)
{
	int	i;
	int	k;

	k = ms_strlen(name);
	i = 0;
	while (env[i])
	{
		if ((!ms_strncmp(env[i], name, k)) && env[i][k] == '=')
			return (env[i] + k + 1);
		i++;
	}
	return (NULL);
}

void	ms_getcwd(char **pwd)
{
	*pwd = getcwd(*pwd, 0);
	if (!*pwd)
	{
		write(2,
			"cd: error retrieving current directory: getcwd:\
cannot access parent directories: No such file or directory\n",
			108);
		*pwd = ms_strdup("");
	}
	return ;
}

int	move_back(char **env)
{
	char	*tmp;

	if (ms_write(1, "", 0))
		return (1);
	tmp = get_env_mine("OLDPWD", env);
	if (!tmp || !tmp[0])
		return (write(2, "minishell: cd: OLDPWD not set\n", 30), 1);
	chdir(tmp);
	printf("%s\n", get_env_mine("OLDPWD", env));
	fflush(stdout);
	return (0);
}

int	ms_move(char **cmd, char **env)
{
	if (((!cmd[1] || !ms_strcmp(cmd[1], "~") || !ms_strcmp(cmd[1], "--")))
		&& !get_env_mine("HOME", env))
		ms_printerror("cd: HOME not set", 0, 0);
	else if (cmd[0] && (!cmd[1] || !ms_strcmp(cmd[1], "~") || !ms_strcmp(cmd[1],
				"--")))
		chdir(get_env_mine("HOME", env));
	else if (cmd[0] && !ms_strcmp(cmd[1], "-"))
		move_back(env);
	else if (cmd[0] && cmd[1])
	{
		if (!cmd[1][0])
			return (0);
		if (chdir(cmd[1]) != 0)
		{
			ms_printerror("cd: ", cmd[1], ": No such file or directory");
			return (1);
		}
	}
	return (0);
}

char	*ms_strjoin_free(char *s1, char const *s2)
{
	size_t	len;
	size_t	cur;
	size_t	i;
	char	*new;

	cur = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ms_strlen(s1) + ms_strlen(s2);
	new = (char *)malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	while (s1[cur] != '\0')
	{
		new[cur] = s1[cur];
		cur++;
	}
	while (s2[i] != '\0')
	{
		new[cur++] = s2[i++];
	}
	new[cur] = '\0';
	free(s1);
	return (new);
}
