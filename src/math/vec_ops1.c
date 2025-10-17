#include "ft_minirt.h"

inline t_vec3	vdivv(t_vec3 a, float k)
{
	return (vec3(a.x / k, a.y / k, a.z / k));
}

inline double	dot_product(t_vec3 origin, t_vec3 direction)
{
	return (origin.x * direction.x + origin.y * direction.y + origin.z
		* direction.z);
}

inline t_vec3	vcross_product(t_vec3 a, t_vec3 b)
{
	return (vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y
			* b.x));
}
