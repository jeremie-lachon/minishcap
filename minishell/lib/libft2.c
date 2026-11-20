#include "minishell.h"

char	*ms_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (0);
}

int	ms_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ms_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

int	skip_quotes(char *str, int *i, int *size, int check)
{
	char	c;
	int		temp;

	temp = *i;
	while (check)
	{
		c = str[*i];
		if (c != '"' && c != '\'')
			break ;
		(*i)++;
		while (str[*i] != c)
			(*i)++;
		(*i)++;
	}
	if (size)
		*size += *i - temp;
	return (1);
}
