#include "get_next_line.h"
#include <stdio.h>

static char	*ft_free(char *buffer, char *buff_rem)
{
	if (buffer)
		free(buffer);
	if (buff_rem)
	{
		free(buff_rem);
		buff_rem = NULL;
	}	
	return (NULL);
}

char	*ft_cut(char **buff_rem, char *buffer)
{
	char	*to_ret;
	char	*tmp;

	if (ft_strchr(*buff_rem, '\n') > -1)
	{
		to_ret = ft_substr(*buff_rem, 0, ft_strchr(*buff_rem, '\n') + 1);
		if (!to_ret)
			return (ft_free(buffer, *buff_rem));
		tmp = *buff_rem;
		*buff_rem = ft_substr(tmp, ft_strchr(*buff_rem, '\n') + 1,
				ft_strlen(*buff_rem) - ft_strchr(*buff_rem, '\n') + 1);
		if (!(*buff_rem))
			return (ft_free(buffer, *buff_rem));
		free(tmp);
	}
	else
	{
		to_ret = *buff_rem;
		*buff_rem = NULL;
	}
	free(buffer);
	return (to_ret);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*buff_rem;
	int			ret_read;

	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(buffer, buff_rem));
	ret_read = 1;
	while (ret_read > 0 && ft_strchr(buff_rem, '\n') == -1)
	{
		ret_read = read(fd, buffer, BUFFER_SIZE);
		if (ret_read == -1)
			return (ft_free(buffer, buff_rem));
		buffer[ret_read] = '\0';
		if (ret_read)
			buff_rem = ft_strjoin(buff_rem, buffer);
		if (!buff_rem)
			return (ft_free(buffer, buff_rem));
	}
	if (buff_rem == NULL || buff_rem[0] == '\0')
		return (ft_free(buff_rem, buffer));
	return (ft_cut(&buff_rem, buffer));
}
