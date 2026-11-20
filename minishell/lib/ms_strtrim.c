#include "minishell.h"

static int	check_char(const char *set, char c)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ms_strtrim(char *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	size;
	char	*str;

	if (!s1)
		return (0);
	if (!set)
		return (s1);
	start = 0;
	end = 0;
	size = ms_strlen(s1);
	while (s1[start] && check_char(set, s1[start]))
		start++;
	if (start == size)
		return (free(s1), ms_calloc(1, 1));
	while (check_char(set, s1[size - 1 - end]))
		end++;
	str = ms_substr(s1, start, size - end - start);
	free(s1);
	if (!str)
		return (0);
	return (str);
}
