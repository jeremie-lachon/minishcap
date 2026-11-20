#include "minishell.h"

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

static int	dollar2(char **str, t_list **lst, char *tmp)
{
	char	*next;

	next = ms_strchrreal(*str, '$');
	if (!next)
		next = ms_strchrreal(*str, '\0');
	if (nodeadder(lst, next, str, 0))
		return (free(tmp), free(next), 1);
	return (0);
}

char	*dollar(char *str, int final, t_execs *exec, t_list *lst)
{
	char	*tmp;
	char	*next;

	tmp = str;
	while (*str)
	{
		if (*str == '$')
		{
			next = getdollar(&str, final, exec);
			if (!next)
				return (substitution_error(str), free(tmp), ms_listfree(&lst,
						subquotefree), NULL);
			if (!listaddback(&lst, listnew(subquotenew(next, 0), subquotefree),
					subquotefree))
				return (free(tmp), NULL);
		}
		else
			if (dollar2(&str, &lst, tmp))
				return (0);
	}
	return (free(tmp), ms_joiner(lst));
}

static int	dollarquote2(char **str, t_list **lst, char *tmp)
{
	char	*next;

	next = ms_strchrreal(*str, '$');
	if (!next)
		next = ms_strchrreal(*str, '\0');
	if (nodeadder(lst, next, str, 0))
		return (free(tmp), 1);
	return (0);
}

char	*dollarquote(char *str, t_execs *exec)
{
	t_list	*lst;
	char	*tmp;
	char	*next;

	lst = 0;
	tmp = str;
	while (*str)
	{
		if (*str == '$')
		{
			next = getdollar(&str, 1, exec);
			if (!next)
				return (free(tmp), ms_listfree(&lst, subquotefree), NULL);
			if (!listaddback(&lst, listnew(subquotenew(next, 0), subquotefree),
					subquotefree))
				return (free(tmp), NULL);
		}
		else
			if (dollarquote2(&str, &lst, tmp))
				return (0);
	}
	return (free(tmp), ms_joiner(lst));
}
