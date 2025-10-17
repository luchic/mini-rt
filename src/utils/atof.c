#include "ft_minirt.h"

double	ft_atof_with_checker(const char *str, int *status)
{
	if (!ft_atof_checker(str))
	{
		set_status(status, 0);
		return (0.0);
	}
	set_status(status, 1);
	return (ft_atof(str));
}
