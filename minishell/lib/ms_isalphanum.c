#include "minishell.h"

int	ms_isalphanum(char chr)
{
	return (!((chr < '0' || chr > '9') && (chr < 'A' || chr > 'Z') && (chr < 'a'
				|| chr > 'z')));
}
