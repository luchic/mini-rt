#include "ft_minirt.h"

void	collide_sphere_plane(t_physics *b, t_plane *pl, float e, float mu)
{
	float	dist;
	t_vec3	n;
	t_vec3	vn;
	t_vec3	vt;

	if (!b || !pl)
		return ;
	n = pl->normal;
	dist = plane_signed_dist(b->pos, pl);
	if (dist >= b->radius)
		return ;
	b->pos = vadd(b->pos, vmul(n, (b->radius - dist)));
	vn = vproj_on_n(b->vel, n);
	vt = vsub(b->vel, vn);
	if (dot_product(vn, n) < 0.0f)
		b->vel = vadd(
				vmul(vn, -e),
				vmul(vt, (1.0f - mu)));
}

void	phys_step(t_physics *b, float dt, float g, t_plane *pl, float e, float mu)
{
	if (!b || !b->active)
		return ;
	b->vel.y = b->vel.y - g * dt;
	b->pos = vadd(b->pos, vmul(b->vel, dt));
	if (pl)
		collide_sphere_plane(b, pl, e, mu);
}
