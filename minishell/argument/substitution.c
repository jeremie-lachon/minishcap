#include "minishell.h"

void	substitution_error(char *str)
{
	char	*tmp;
	int		size;

	size = 0;
	tmp = str + 1;
	if (*tmp == '{')
	{
		while (tmp[size + 1] && tmp[size] != '}')
			size++;
	}
	else
	{
		while (tmp[size + 1] && !iswhite(tmp[size]) && tmp[size] != '\''
			&& tmp[size] != '"')
			size++;
	}
	tmp = ms_substr(str, 0, size + 2);
	if (!tmp)
		return ;
	ms_printerror("minishell: ", tmp, ": bad substitution");
	free(tmp);
}

static char	*untilnonalpha(char **str, t_execs *exec)
{
	int		check;
	char	*tmp;
	char	*final;

	tmp = *str + 1;
	check = (*tmp == '{');
	tmp += check;
	while (*tmp && !((*tmp < '0' || *tmp > '9') && (*tmp < 'A' || *tmp > 'Z')
			&& (*tmp < 'a' || *tmp > 'z')))
		tmp++;
	if (check && (*tmp != '}' || *str + 2 == tmp))
		return (0);
	final = ms_substr(*str, 1 + check, tmp - *str - 1 - check);
	if (!final)
		return (0);
	*str = tmp + check;
	if (!exec)
		tmp = getenv(final);
	else
		tmp = get_env(final, exec->shell->env);
	free(final);
	if (!tmp)
		return (ms_calloc(sizeof(char), 1));
	return (tmp);
}

static void	inc(char **str, int inc)
{
	*str += inc;
}

char	*getdollar(char **str, int final, t_execs *exec)
{
	if (!*(*str + 1) && !final)
		return (inc(str, 1), ms_calloc(1, sizeof(char)));
	else if ((!*(*str + 1) && final) || (!ms_isalphanum(*(*str + 1))
			&& *(*str + 1) != '{' && *(*str + 1) != '?'))
	{
		*str += 1;
		if (*((*str)++) == '$')
			return (ms_strdup("$$"));
		return (inc(str, -1), ms_strdup("$"));
	}
	else if (!ms_strncmp((*str + 1), "{?", 2))
	{
		if (*(*str + 3) != '}')
			return (0);
		return (inc(str, 4), ms_itoa(exec->ret));
	}
	else if (*(*str + 1) == '?')
		return (inc(str, 2), ms_itoa(exec->ret));
	return (untilnonalpha(str, exec));
}
