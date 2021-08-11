#include "get_next_line_bonus.h"

int	ft_strchr(const char *s, int c)
{
	char	*char_s;
	char	char_c;
	int		i;

	i = 0;
	if (s == NULL)
		return (-1);
	char_c = (char) c;
	char_s = (char *) s;
	while (char_s[i])
	{
		if (char_s[i] == char_c)
			return (i);
		i++;
	}
	if (c == '\0' && char_s[i] == '\0')
		return (i);
	return (-1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	count;
	char	*new_str;

	if (s1 == NULL)
		s1 = malloc(0);
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	count = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new_str == NULL)
		return (NULL);
	while (s1[count])
	{
		new_str[count] = s1[count];
		count++;
	}
	count = 0;
	while (s2[count])
	{
		new_str[count + ft_strlen(s1)] = s2[count];
		count++;
	}
	new_str[count + ft_strlen(s1)] = '\0';
	free(s1);
	return (new_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	size;

	i = 0;
	if (ft_strlen(s) < start)
	{
		sub_str = (malloc(sizeof(char)));
		if (sub_str == NULL)
			return (NULL);
		return (sub_str);
	}
	size = len;
	if (ft_strlen(s) < len)
		size = ft_strlen(s);
	sub_str = malloc(sizeof(char) * size + 1);
	if (sub_str == NULL)
		return (NULL);
	while (s[start] && i < len)
		sub_str[i++] = s[start++];
	sub_str[i] = '\0';
	return (sub_str);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	if (str == NULL)
		return (0);
	count = 0;
	while (*(str + count))
		count++;
	return (count);
}

char	*ft_strjoin_dup(char *buff_rem, char *buffer)
{
	char	*tmp;
	char	*to_ret;

	tmp = ft_strdup(buffer);
	if (!tmp)
		return (NULL);
	to_ret = ft_strjoin(buff_rem, tmp);
	free(tmp);
	return (to_ret);
}
