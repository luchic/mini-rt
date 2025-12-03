
#include "ft_minirt.h"

t_vec3	vec3_project_on_axis(t_vec3 v, t_vec3 axis)
{
	return (vmul(axis, dot_product(v, axis)));
}

t_vec3	vec3_reject_from_axis(t_vec3 v, t_vec3 axis)
{
	return (vsub(v, vec3_project_on_axis(v, axis)));
}
