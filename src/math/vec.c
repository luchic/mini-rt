#include "ft_minirt.h"

t_vec3	vec3(float x, float y, float z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

float	vlen(t_vec3 a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3	vnorm(t_vec3 a)
{
	float	length;

	length = vlen(a);
	if (length < EPS)
		return (vec3(0, 0, 0));
	return (vec3(a.x / length, a.y / length, a.z / length));
}

t_ray	ray(t_vec3 o, t_vec3 d)
{
	t_ray	r;

	r.o = o;
	r.d = d;
	return (r);
}

t_vec3	vclamp01(t_vec3 c)
{
	t_vec3	o;

	o = c;
	if (o.x < 0)
		o.x = 0;
	if (o.x > 1)
		o.x = 1;
	if (o.y < 0)
		o.y = 0;
	if (o.y > 1)
		o.y = 1;
	if (o.z < 0)
		o.z = 0;
	if (o.z > 1)
		o.z = 1;
	return (o);
}
