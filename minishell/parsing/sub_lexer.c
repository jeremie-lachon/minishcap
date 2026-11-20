#include "minishell.h"

static int	*type_setter(int f, int s)
{
	int	*i;

	i = malloc(sizeof(int) * 2);
	i[0] = f;
	i[1] = s;
	return (i);
}

static int	type_return(int *type, char symbol, char *str, int *i)
{
	int	j[2];

	j[0] = type[0];
	j[1] = type[1];
	free(type);
	if (str[*i + 1] == symbol)
	{
		(*i)++;
		return (j[1]);
	}
	return (j[0]);
}

int	and_return(t_lexer **lexer, char *str, int *i)
{
	t_lexer	*new;

	if (str[*i + 1] == '&')
	{
		new = ms_calloc(sizeof(*new), 1);
		if (!new)
			return (1);
		new->type = LEX_AND;
		*i += 2;
		return (ms_lstadd_back(lexer, &new), 0);
	}
	else
	{
		return (add_lex_node(lexer, str, i), 0);
	}
	return (1);
}

int	sub_lexer(t_lexer **lex, char *str, int *i)
{
	t_lexer	*new;

	new = ms_calloc(sizeof(*new), 1);
	if (!new)
		return (1);
	if (str[*i] == '>')
		new->type = type_return(type_setter(LEX_REDIRIN, \
		LEX_APPEND), '>', str, i);
	else if (str[*i] == '<')
		new->type = type_return(type_setter(LEX_REDIROUT, \
		LEX_HERE), '<', str, i);
	else if (str[*i] == '(')
		new->type = LEX_OPEN;
	else if (str[*i] == ')')
		new->type = LEX_CLOSE;
	else if (str[*i] == '|')
		new->type = type_return(type_setter(LEX_PIPE, LEX_OR), '|', str, i);
	(*i)++;
	return (ms_lstadd_back(lex, &new), 0);
}
