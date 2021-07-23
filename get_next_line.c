#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (*(str + count))
		count++;
	return (count);
}

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

void	*ft_memset(void *b, int c, size_t n)
{
	size_t	i;
	char	*char_b;

	if (b == NULL)
		return (NULL);
	char_b = (char *) b;
	i = 0;
	while (i < n)
	{
		char_b[i] = c;
		i++;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*to_ret;
	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	to_ret = malloc(count * size);
	if (!to_ret)
		return (NULL);
	ft_bzero(to_ret, size * count);
	return (to_ret);
}

char    *get_all_lines(char *str, int fd)
{
    int     read_ret;
    char    buffer[BUFFER_SIZE + 1];

    str = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!str)
        return (NULL);
   read_ret = read(fd, buffer, BUFFER_SIZE);
   while (read_ret > 0)
   {
       buffer[read_ret] = '\0';
       str = ft_strjoin(str, buffer);
       read_ret  = read(fd, buffer, BUFFER_SIZE);
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

char    *get_next_line(int fd)
{
    static char		*str;
    char    		*to_ret;
    int 			i;
    
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

#include <fcntl.h>


int main()
{
    int     fd;
    char    *res;
    fd = open("multiple_line_no_nl",O_RDONLY);
    if (fd == -1)
    {
        printf("MERDE");
        return (-1);
    }
    res = get_next_line(fd);
    while (*res)
    {
		printf("%s", res);
        res = get_next_line(fd);
    }
    return (0);
}