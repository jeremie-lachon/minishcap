#include "minishell.h"

char	*ms_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	size;

	i = 0;
	if (!s)
		return (0);
	if (start > (unsigned int)ms_strlen(s))
		size = 0;
	else if ((unsigned int)ms_strlen(s + start) > len)
		size = len;
	else
		size = (unsigned int)ms_strlen(s + start);
	new = ms_calloc(sizeof(char), size + 1);
	if (!new)
		return (0);
	if (start > (unsigned int)ms_strlen(s))
		return (new);
	while (s[start] && i < len)
		new[i++] = s[start++];
	return (new);
}
