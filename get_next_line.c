#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	count;
	char	*new_str;
	size_t	s1_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	count = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)));
	if (new_str == NULL)
		return (NULL);
	while (s1[count] && count < s1_len)
	{
		new_str[count] = s1[count];
		count++;
	}
	count = 0;
	while (s2[count])
	{
		new_str[count + s1_len] = s2[count];
		count++;
	}
	new_str[count + s1_len] = '\0';
	return (new_str);
}

char	*get_all_lines(char *str, int fd)
{
	int		read_ret;
	char	buffer[BUFFER_SIZE + 1];

	str = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!str)
		return (NULL);
	read_ret = read(fd, buffer, BUFFER_SIZE);
	while (read_ret > 0)
	{
		buffer[read_ret] = '\0';
		str = ft_strjoin(str, buffer);
		read_ret = read(fd, buffer, BUFFER_SIZE);
	}
	return (str);
}

char	*ft_strncpy(const char *s, int size)
{
	char	*to_ret;

	to_ret = malloc(sizeof(char) * (size));
	if (to_ret == NULL)
		return (NULL);
	to_ret[size] = '\0';
	size--;
	while (size >= 0)
	{
		to_ret[size] = s[size];
		size--;
	}
	return (to_ret);
}

char	*get_next_line(int fd)
{
	static char		*str;
	char			*to_ret;
	int				i;

	i = 0;
	if (fd == -1)
		return (NULL);
	if (!str)
	{
		str = get_all_lines(str, fd);
		if (!str)
			return (NULL);
	}
	while (str[i] && str[i] != '\n')
		i++;
	to_ret = ft_strncpy(str, i + 1);
	if (!to_ret)
	{
		free(str);
		return (NULL);
	}
	str = &str[i + 1];
	return (to_ret);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
//     int     fd;
//     char    *res;
//     fd = open("multiple_line_with_nl",O_RDONLY);
//     if (fd == -1)
//     {
//         printf("MERDE");
//         return (-1);
//     }
//     res = get_next_line(fd);
//     while (*res)
//     {
// 		printf("%s", res);
//         res = get_next_line(fd);
//     }
//     return (0);
// }