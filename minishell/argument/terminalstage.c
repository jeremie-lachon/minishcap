#include "minishell.h"

static char	*listjoiner(t_list **quote, t_list *lst, int i, char *str)
{
	t_list		*tmp;
	t_subquote	*node;
	int			*pair;

	tmp = lst;
	while (tmp)
	{
		node = tmp->data;
		if (node->check)
		{
			pair = ms_calloc(sizeof(int), 2);
			pair[0] = i;
			i += ms_strlen(node->str);
			pair[1] = i - 1;
			if (!listaddback(quote, listnew(pair, free), free))
				return (0);
		}
		else
			i += ms_strlen(node->str);
		str = ms_strcatter(str, node->str);
		if (!str)
			return (ms_listfree(&lst, subquotefree), NULL);
		tmp = tmp->next;
	}
	return (ms_listfree(&lst, subquotefree), ms_strtrim(str, " \t\n\v\f\r"));
}

static t_list	*quotetostr(t_list *node)
{
	t_list	*tmp;

	tmp = node;
	node = listnew(ms_strdup(((t_subquote *)node->data)->str), free);
	ms_listfree(&tmp, subquotefree);
	return (node);
}

static int	resplitter2(char *str, t_list *lst, t_list **final)
{
	t_list	*node;

	node = ms_calloc(sizeof(t_list), 1);
	if (!node)
		return (free(str), ms_listfree(&lst, free), 1);
	node->data = 0;
	node->next = 0;
	if (!listaddback(final, node, free))
		return (free(str), ms_listfree(&lst, free), 1);
	return (0);
}

t_list	*resplitter(t_list *lst, t_list *quote, t_list *final, int i)
{
	char	*str;
	t_list	*node;

	str = listjoiner(&quote, lst, 0, 0);
	lst = quote;
	while (str[i])
	{
		while (str[i] && iswhite(str[i]))
			i++;
		if (!str[i])
			break ;
		node = sub_unquoted(str, &quote, &i, 0);
		if (node->next || ((t_subquote *)node->data)->check)
			node = star(node);
		else
			node = quotetostr(node);
		if (!listaddback(&final, node, free))
			return (free(str), ms_listfree(&lst, free), NULL);
	}
	if (!i)
		if (resplitter2(str, lst, &final))
			return (0);
	return (free(str), ms_listfree(&lst, free), final);
}
