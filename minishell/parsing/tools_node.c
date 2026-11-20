#include "minishell.h"

t_lexer	*ms_lstlast(t_lexer *lst)
{
	if (!lst)
		return (0);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

void	ms_lstadd_back(t_lexer **lst, t_lexer **new)
{
	t_lexer	*temp;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = (*new);
	else
	{
		temp = *lst;
		temp = ms_lstlast(temp);
		temp->next = (*new);
		(*new)->prev = temp;
	}
}

void	ms_pipeaddback(t_shell **shell, t_herepipe *new)
{
	t_herepipe	*temp;

	if ((*shell)->pipe == NULL)
	{
		(*shell)->pipe = new;
		return ;
	}
	temp = (*shell)->pipe;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
