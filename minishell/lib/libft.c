#include "minishell.h"

char	*ms_strchrreal(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (*s == c)
		return (s);
	return (0);
}

char	*ms_strchr2(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (s[i + 1] == c)
			{
				return (s);
			}
		}
		i++;
	}
	return (0);
}

size_t	ms_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ms_strlen (src);
	if (size <= 0 || !(dst))
		return (len);
	while (i < len && i < size - 1)
		*dst++ = src[i++];
	*dst = 0;
	return (len);
}

char	*ms_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	cur;
	size_t	i;
	char	*new;

	cur = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ms_strlen(s1) + ms_strlen(s2);
	new = (char *)malloc(sizeof (char) * len + 1);
	if (!new)
		return (NULL);
	while (s1[cur] != '\0')
	{
		new[cur] = s1[cur];
		cur++;
	}
	while (s2[i] != '\0')
	{
		new[cur++] = s2[i++];
	}
	new[cur] = '\0';
	return (new);
}
