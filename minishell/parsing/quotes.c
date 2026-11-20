#include "minishell.h"

static int	quote_skipper(char **s, char end)
{
	char	*str;

	str = (*s);
	++str;
	while (*str && *str != (char)end)
		++str;
	if (*str == '\0')
		return (1);
	*s = str;
	return (0);
}

int	quote_check(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			if (quote_skipper(&str, *str))
				return (1);
		++str;
	}
	return (0);
}
