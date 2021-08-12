#include "get_next_line_bonus.h"

char	*ft_free(char **buff_rem, int fd)
{
	if (buff_rem && buff_rem[fd])
	{
		free(buff_rem[fd]);
		buff_rem[fd] = NULL;
	}	
	return (NULL);
}

char	*ft_cut(char **buff_rem, int fd)
{
	char	*to_ret;
	char	*tmp;

	if (ft_strchr(buff_rem[fd], '\n') > -1)
	{
		to_ret = ft_substr(buff_rem[fd], 0, ft_strchr(buff_rem[fd], '\n') + 1);
		if (!to_ret)
			return (ft_free(buff_rem, fd));
		tmp = buff_rem[fd];
		buff_rem[fd] = ft_substr(tmp, ft_strchr(tmp, '\n') + 1,
				ft_strlen(tmp) - ft_strchr(tmp, '\n') + 1);
		free(tmp);
		if (!(buff_rem[fd]))
		{
			free(to_ret);
			return (ft_free(buff_rem, fd));
		}
	}
	else
	{
		to_ret = buff_rem[fd];
		buff_rem[fd] = NULL;
	}
	return (to_ret);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*char_dst;
	const char	*char_src;
	size_t		i;

	i = 0;
	if (dst == src || n == 0)
		return (dst);
	char_dst = (char *) dst;
	char_src = (const char *) src;
	while (i < n)
	{
		char_dst[i] = char_src[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	void	*to_ret;
	size_t	s1_len;

	if (s1 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	to_ret = malloc(sizeof(char) * (s1_len + 1));
	if (to_ret == NULL)
		return (NULL);
	ft_memcpy(to_ret, s1, s1_len + 1);
	return (to_ret);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*buff_rem[OPEN_MAX];
	int			ret_read;

	if (fd == -1 || BUFFER_SIZE < 1 || fd >= OPEN_MAX)
		return (NULL);
	ret_read = 1;
	while (ret_read > 0 && ft_strchr(buff_rem[fd], '\n') == -1)
	{
		ret_read = read(fd, buffer, BUFFER_SIZE);
		if (ret_read == -1)
			return (ft_free(buff_rem, fd));
		buffer[ret_read] = '\0';
		if (ret_read)
		{
			buff_rem[fd] = ft_strjoin_dup(buff_rem[fd], buffer);
			if (!buff_rem[fd])
				return (ft_free(buff_rem, fd));
		}
	}
	if (!buff_rem[fd] || buff_rem[fd][0] == '\0')
		return (ft_free(buff_rem, fd));
	return (ft_cut(buff_rem, fd));
}
