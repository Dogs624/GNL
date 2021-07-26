#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *b, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

#endif