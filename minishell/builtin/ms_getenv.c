#include "minishell.h"

static char	*ms_substrr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*copy;

	if (start > ms_strlen(s))
		return (ms_calloc(1, 1));
	if (len + start <= ms_strlen(s))
		copy = (char *)malloc(sizeof(char) * (len + 1));
	else
		copy = (char *)malloc(sizeof(char) * (ms_strlen(s + start) + 1));
	if (!copy)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			copy[j] = s[i];
			j++;
		}
		i++;
	}
	copy[j] = 0;
	return (copy);
}

char	*get_env(char *name, char **env)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		new = ms_substrr(env[i], 0, j);
		if (ms_strcmp(new, name) == 0)
		{
			free(new);
			return (env[i] + j + 1);
		}
		free(new);
		i++;
	}
	return (NULL);
}
