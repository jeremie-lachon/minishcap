#include "minishell.h"

static int	ms_countwords(char const *s, char c, int *index)
{
	int	i;
	int	sum;
	int	check;

	i = 0;
	sum = 0;
	check = 1;
	while (s[i])
	{
		if (s[i] == c)
			check = 1;
		else if (check == 1)
		{
			check = 0;
			if (index[2] == sum)
				index[0] = i;
			sum++;
		}
		i++;
	}
	return (sum);
}

static int	ms_findlength(char const *s, char c, int *index)
{
	int	i;

	i = index[0];
	while (s[i] && s[i] != c)
		i++;
	index[1] = i;
	return (i - index[0]);
}

static void	ms_fillsplit(char *word, char const *s, int *index, char *bonus)
{
	int	i;

	i = 0;
	while (index[0] < index[1])
		*word++ = s[index[0]++];
	while (bonus[i])
		*word++ = bonus[i++];
	*word = 0;
}

static char	**ms_freesplit(char **res, int n)
{
	while (n + 1)
		free(res[n--]);
	free(res);
	return (0);
}

char	**ms_pathsplit(char const *s, char c, char *bonus)
{
	int		index[4];
	char	**res;
	int		size;

	size = ms_strlen(bonus);
	if (!s)
		return (0);
	index[2] = 0;
	index[3] = ms_countwords(s, c, index);
	res = malloc((index[3] + 1) * sizeof(char *));
	if (!res)
		return (0);
	while (index[2] < index[3])
	{
		ms_countwords(s, c, index);
		res[index[2]] = ms_calloc(sizeof(char),
				(ms_findlength(s, c, index) + size +1));
		if (!res[index[2]])
			return (ms_freesplit(res, index[2]));
		ms_fillsplit(res[index[2]], s, index, bonus);
		index[2]++;
	}
	res[index[2]] = 0;
	return (res);
}
