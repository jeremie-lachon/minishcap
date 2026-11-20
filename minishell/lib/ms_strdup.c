#include "minishell.h"

char	*ms_strdup(char *s)
{
	size_t	i;
	char	*new;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	new = malloc((i + 1) * sizeof(char));
	if (!new)
		return (0);
	new[i] = 0;
	while (i--)
		new[i] = s[i];
	return (new);
}
