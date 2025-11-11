#include "ft_minirt.h"
#include <limits.h>

void	set_status(int *status, int value)
{
	if (status)
		*status = value;
}

int	ft_atoi_with_checker(const char *str, int *status)
{
	if (!ft_atoi_checker(str))
	{
		set_status(status, 0);
		return (0);
	}
	set_status(status, 1);
	return (ft_atoi(str));
}
