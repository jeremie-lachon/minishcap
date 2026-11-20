#include "minishell.h"

static char	*untilnonalpha(char **str)
{
	char	*tmp;
	char	*final;

	tmp = *str + 1;
	while (*tmp && !((*tmp < '0' || *tmp > '9') && (*tmp < 'A' || *tmp > 'Z')
			&& (*tmp < 'a' || *tmp > 'z')))
		tmp++;
	final = ms_substr(*str, 0, tmp - *str);
	if (!final)
		return (0);
	*str = tmp;
	return (final);
}

static char	*ms_joiner(t_list *lst)
{
	char	*res;
	int		size;
	t_list	*tmp;

	tmp = lst;
	size = 0;
	while (tmp)
	{
		size += ms_strlen(((t_subquote *)tmp->data)->str);
		tmp = tmp->next;
	}
	tmp = lst;
	res = ms_calloc(sizeof(char), size + 1);
	if (!res)
		return (ms_listfree(&lst, subquotefree), NULL);
	while (tmp)
	{
		res = ms_strcat(res, ((t_subquote *)tmp->data)->str);
		tmp = tmp->next;
	}
	return (ms_listfree(&lst, subquotefree), res);
}

char	*getdollarhere(char **str, int final)
{
	if (!*(*str + 1) && !final)
	{
		*str += 1;
		return (ms_calloc(1, sizeof(char)));
	}
	else if ((!*(*str + 1) && final) || !ms_isalphanum(*(*str + 1)))
	{
		if (*(*str + 1) == '$')
		{
			*str += 2;
			return (ms_strdup("$$"));
		}
		*str += 1;
		return (ms_strdup("$"));
	}
	return (untilnonalpha(str));
}

char	*dollarhere(char *str, int final, t_list *lst, char *tmp)
{
	char	*next;

	lst = 0;
	tmp = str;
	while (*str)
	{
		if (*str == '$')
		{
			next = getdollarhere(&str, final);
			if (!next)
				return (free(tmp), ms_listfree(&lst, subquotefree), NULL);
			if (!listaddback(&lst, listnew(subquotenew(next, 0), subquotefree),
					subquotefree))
				return (free(tmp), NULL);
		}
		else
		{
			next = ms_strchrreal(str, '$');
			if (!next)
				next = ms_strchrreal(str, '\0');
			if (nodeadder(&lst, next, &str, 0))
				return (free(tmp), free(next), NULL);
		}
	}
	return (free(tmp), ms_joiner(lst));
}

char	*dollarquotehere(char *str, t_list *lst, char *tmp)
{
	char	*next;

	lst = 0;
	tmp = str;
	while (*str)
	{
		if (*str == '$')
		{
			next = getdollarhere(&str, 1);
			if (!next)
				return (free(tmp), ms_listfree(&lst, subquotefree), NULL);
			if (!listaddback(&lst, listnew(subquotenew(next, 0), subquotefree),
					subquotefree))
				return (free(tmp), NULL);
		}
		else
		{
			next = ms_strchrreal(str, '$');
			if (!next)
				next = ms_strchrreal(str, '\0');
			if (nodeadder(&lst, next, &str, 0))
				return (free(tmp), NULL);
		}
	}
	return (free(tmp), ms_joiner(lst));
}
