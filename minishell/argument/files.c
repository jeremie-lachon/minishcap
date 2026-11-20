#include "minishell.h"

static int	checkfilelist(t_list *files)
{
	while (files)
	{
		if (((t_file *)files->data)->search)
			return (0);
		files = files->next;
	}
	return (1);
}

static t_list	*filejoin(t_list *files, t_list *list)
{
	t_list	*new;
	t_list	*tmp;
	char	*str;
	int		size;

	size = 0;
	ms_listfree(&files, filefree);
	tmp = list;
	while (tmp)
	{
		size += ms_strlen(((t_subquote *)tmp->data)->str);
		tmp = tmp->next;
	}
	new = ms_calloc(sizeof(t_list), 1);
	new->next = 0;
	str = ms_calloc(sizeof(char), size + 1);
	tmp = list;
	while (tmp)
	{
		str = ms_strcat(str, ((t_subquote *)tmp->data)->str);
		tmp = tmp->next;
	}
	new->data = str;
	return (ms_listfree(&list, subquotefree), new);
}

static void	filecheck2(t_file *tmp, char *str, int size, int mode)
{
	int	sizetmp;

	if (!mode)
	{
		if (ms_strncmp(tmp->search, str, size))
			tmp->search = 0;
		else
			tmp->search = tmp->search + size;
	}
	else if (mode == 1)
		tmp->search = ms_strstr(tmp->search, str);
	else
	{
		sizetmp = ms_strlen(tmp->search);
		if (sizetmp < size || (sizetmp >= size
				&& ms_strncmp(tmp->search + sizetmp - size, str, size)))
			tmp->search = 0;
	}
}

void	filecheck(t_list *files, t_list *node, int mode)
{
	t_file	*tmp;
	char	*str;
	int		size;

	str = ((t_subquote *)node->data)->str;
	if (!mode || mode == 2)
		size = ms_strlen(str);
	while (files)
	{
		tmp = files->data;
		if (!tmp->search)
		{
			files = files->next;
			continue ;
		}
		filecheck2(tmp, str, size, mode);
		files = files->next;
	}
}

t_list	*filelist(t_list *files, t_list *list)
{
	t_list	*copy;

	copy = files;
	if (checkfilelist(files))
		return (filejoin(files, list));
	ms_listfree(&list, subquotefree);
	list = 0;
	while (copy)
	{
		if (((t_file *)copy->data)->search)
			if (!listaddback(&list,
					listnew(ms_strdup(((t_file *)copy->data)->filename), free),
					free))
				return (ms_listfree(&files, filefree), NULL);
		copy = copy->next;
	}
	ms_listfree(&files, filefree);
	return (list);
}
