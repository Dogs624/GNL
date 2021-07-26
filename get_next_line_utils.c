#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (*(str + count))
		count++;
	return (count);
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