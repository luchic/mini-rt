#include "ft_minirt.h"

t_vec3	vproj_on_n(t_vec3 v, t_vec3 n)
{
	return (vmul(n, dot_product(v, n)));
}

float	plane_signed_dist(t_vec3 p, t_plane *pl)
{
	return (dot_product(vsub(p, pl->position), pl->normal));
}
