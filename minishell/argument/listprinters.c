#include "minishell.h"

void	subquoteprint(void *data)
{
	printf("QUOTE: %s %d\n", ((t_subquote *)data)->str,
		((t_subquote *)data)->check);
}

void	strprint(void *data)
{
	printf("STRING: %s\n", (char *)data);
}

void	fileprint(void *data)
{
	printf("FILE: %s\n", ((t_file *)data)->filename);
}

void	intprint(void *data)
{
	printf("INTS: %d %d\n", ((int *)data)[0], ((int *)data)[1]);
}

void	printlist(t_list *list, void (*print)(void *))
{
	while (list)
	{
		print(list->data);
		list = list->next;
	}
}
