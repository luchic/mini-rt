#include "ft_minirt.h"

void	*emalloc(size_t size)
{
	void	*ptr;

	ptr = ft_malloc(size);
	if (!ptr)
		ft_exit("malloc failed", 1);
	return (ptr);
}
