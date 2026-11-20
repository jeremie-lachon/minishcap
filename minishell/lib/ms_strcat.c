#include "minishell.h"

char	*ms_strcat(char *dest, char *src)
{
	char	*start;

	if (!dest || !src)
		return (dest);
	start = dest;
	while (*dest)
		dest++;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (start);
}
