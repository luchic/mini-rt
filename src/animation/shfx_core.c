#include "ft_minirt.h"

t_shfx	*fx(void)
{
	static t_shfx	st;

	return (&st);
}

int	impact_happened(t_sphere *big, t_plane *pl)
{
	if (!big)
		return (0);
	if (pl)
		return (plane_signed_dist(big->center, pl) <= big->radius);
	return (big->center.y <= big->radius);
}

void	shfx_trigger(t_app *a)
{
	t_shfx		*st;
	t_sphere	*s;

	if (!a)
		return ;
	rng_seed(a, 0xC0FFEEu);
	a->last_ts = mlx_get_time();
	st = fx();
	st->enabled = 1;
	st->phase = 0;
	st->big_obj = find_first(&a->scene, OBJ_SPHERE);
	st->ground = find_ground(&a->scene);
	st->g = 9.8f;
	st->bounce = 0.35f;
	st->fric = 0.10f;
	st->count = 0;
	if (!st->big_obj || !st->big_obj->ptr)
		return ;
	s = (t_sphere *)st->big_obj->ptr;
	if (s->center.y < s->radius + 0.1f)
		s->center.y = s->radius + 0.1f;
}
