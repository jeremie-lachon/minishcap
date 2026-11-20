#include "minishell.h"

t_list	*listnew(void *data, void (*f)(void *))
{
	t_list	*new;

	if (!data)
		return (0);
	new = ms_calloc(sizeof(t_list), 1);
	if (!new)
		return (f(data), NULL);
	new->next = 0;
	new->data = data;
	return (new);
}

t_list	*listaddback(t_list **lst, t_list *new, void (*f)(void *))
{
	t_list	*tmp;

	if (!new)
		return (ms_listfree(lst, f), NULL);
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (*lst);
}

int	listsize(t_list *list)
{
	int	size;

	size = 0;
	while (list)
	{
		list = list->next;
		size++;
	}
	return (size);
}

int	ms_listfree(t_list **lst, void (*f)(void *))
{
	if (!*lst)
		return (1);
	if ((*lst)->next)
		ms_listfree(&(*lst)->next, f);
	f((*lst)->data);
	free(*lst);
	*lst = 0;
	return (0);
}
