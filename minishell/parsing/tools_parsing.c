#include "minishell.h"

int	lfsymbol(char **ptr, char *c)
{
	char	*temp;

	temp = *ptr;
	while (*temp && ms_strchr(" \t\n\r\v", *temp))
		temp++;
	*ptr = temp;
	return (*ptr && ms_strchr(c, *temp));
}

int	lfsymbol2(char **ptr, char *c)
{
	char	*temp;

	temp = *ptr;
	while (*temp && ms_strchr(" \t\n\r\v", *temp))
		temp++;
	*ptr = temp;
	return (*ptr && ms_strchr(c, *temp) && ms_strchr(c, *(temp + 1)));
}
