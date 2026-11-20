#include "minishell.h"

static char	*findnextquote(char *str)
{
	char	*dquote;
	char	*squote;

	if (*str == '"' || *str == '\'')
		return (ms_strchrreal(str + 1, *str) + 1);
	dquote = ms_strchrreal(str, '"');
	squote = ms_strchrreal(str, '\'');
	if (!dquote)
	{
		if (!squote)
			return (ms_strchrreal(str, '\0'));
		return (squote);
	}
	else if (!squote)
		return (dquote);
	else if (dquote > squote)
		return (squote);
	return (dquote);
}

int	nodeadder(t_list **lst, char *str1, char **str2, int check)
{
	char	*tmp;

	tmp = ms_substr(*str2, 0, (size_t)(str1 - *str2));
	if (!tmp)
		return (free(tmp), ms_listfree(lst, subquotefree), 1);
	*str2 = str1;
	if (!listaddback(lst, listnew(subquotenew(tmp, check), subquotefree),
			subquotefree))
		return (1);
	return (0);
}

t_list	*expansion(char *str)
{
	t_list	*lst;

	lst = 0;
	while (*str)
	{
		if (nodeadder(&lst, findnextquote(str), &str, (*str == '\''
					|| *str == '"')))
			return (0);
	}
	return (lst);
}
