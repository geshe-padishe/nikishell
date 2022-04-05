#include "dynarray.h"

void	ft_memset(void *mem, int c, size_t size)
{
	size_t	i;
	char	*ptr;

	if (!mem)
		return ;
	i = 0;
	ptr = (char *)mem;
	while (i < size)
	{
		ptr[i] = c;
		i++;
	}
}

void	ft_memcpy(void *dest, void *src, size_t size)
{
	char	*d;
	char	*s;

	d = dest;
	s = src;
	while (size--)
		*d++ = *s++;
}
