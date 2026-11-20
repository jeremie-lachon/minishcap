#include "minishell.h"

static char	*untilnonalpha(char *str, int *i, t_execs *exec)
{
	int		check;
	int		j;
	char	*final;
	char	*tmp;

	j = *i + 1;
	check = (str[j] == '{');
	j += check;
	while (str[j] && ms_isalphanum(str[j]))
		j++;
	if (check && (str[j] != '}' || *i + 2 == j))
		return (0);
	final = ms_substr(str + *i, 1 + check, j - *i - 1 - check);
	if (!final)
		return (0);
	*i = j + check;
	if (!exec)
		tmp = getenv(final);
	else
		tmp = get_env(final, exec->shell->env);
	free(final);
	if (!tmp)
		return (ms_calloc(sizeof(char), 1));
	return (tmp);
}

char	*getdollarherehere(char *str, int *i, t_execs *exec)
{
	if (!str[*i + 1] || (!ms_isalphanum(str[*i + 1]) && str[*i +1] != '{'))
	{
		*i += 1;
		if (str[*i] == '$')
		{
			*i += 1;
			return (ms_strdup("$$"));
		}
		return (ms_strdup("$"));
	}
	else if (!ms_strncmp(str + *i + 1, "{?", 2))
	{
		if (!str[*i + 1] || str[*i + 2] != '}')
			return (0);
		*i += 3;
		return (ms_itoa(exec->ret));
	}
	else if (str[*i + 1] == '?')
	{
		*i += 1;
		return (ms_itoa(exec->ret));
	}
	return (untilnonalpha(str, i, exec));
}

void	indexdollar(char *str, int *i, int fd, t_list **list)
{
	char	*dollar;
	int		j;

	j = *i;
	dollar = (char *)(*list)->data;
	*list = (*list)->next;
	write(fd, dollar, ms_strlen(dollar));
	if (str[j + 1] == '{')
	{
		while (str[j] != '}')
			j++;
		j++;
	}
	else if (str[j + 1] == '$')
	{
		j += 2;
	}
	else
	{
		j++;
		while (str[j] && ms_isalphanum(str[j]))
			j++;
	}
	*i = j;
}
