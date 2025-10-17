#include "ft_minirt.h"

static int	in_range(float v, float lo, float hi)
{
	return (v >= lo && v <= hi);
}

static int	parse_axis_component(const char *axis_str, float *axis)
{
	int		status;
	float	result;

	status = 0;
	result = ft_atof_with_checker(axis_str, &status);
	if (!status)
		return (0);
	*axis = result;
	return (1);
}

int	parse_v3(const char *s, t_vec3 *v)
{
	char	**p;
	float	x;
	float	y;
	float	z;

	p = split_by(s, ',');
	if (!p || !p[0] || !p[1] || !p[2] || p[3])
		return (free_split(p), 0);
	if (!parse_axis_component(p[0], &x))
		return (free_split(p), 0);
	if (!parse_axis_component(p[1], &y))
		return (free_split(p), 0);
	if (!parse_axis_component(p[2], &z))
		return (free_split(p), 0);
	free_split(p);
	*v = vec3(x, y, z);
	return (1);
}

int	parse_norm_v3(const char *s, t_vec3 *v)
{
	if (!parse_v3(s, v))
		return (0);
	if (!in_range(v->x, -1, 1) || !in_range(v->y, -1, 1)
		|| !in_range(v->z, -1, 1))
		return (0);
	*v = vnorm(*v);
	return (1);
}