#include "ft_minirt.h"

inline t_vec3	vadd(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x + b.x, a.y + b.y, a.z + b.z));
}

inline t_vec3	vsub(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x - b.x, a.y - b.y, a.z - b.z));
}

inline t_vec3	vmul(t_vec3 a, float k)
{
	return (vec3(a.x * k, a.y * k, a.z * k));
}

t_vec3	vec_scale(t_vec3 v, float k)
{
	return (vec3(v.x * k, v.y * k, v.z * k));
}
