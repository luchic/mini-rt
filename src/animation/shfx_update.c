#include "ft_minirt.h"

void	shfx_update(t_app *a, double now)
{
	t_shfx	*st;
	double	dt;
	int		i;

	if (!a)
		return ;
	st = fx();
	if (!st->enabled || !st->big_obj || !st->big_obj->ptr)
		return ;
	dt = now - a->last_ts;
	if (dt < (1.0 / 60.0))
		return ;
	if (dt > 0.05)
		dt = 0.05;
	a->last_ts = now;
	if (st->phase == 0)
	{
		t_sphere	*s;

		s = (t_sphere *)st->big_obj->ptr;
		s->center.y = s->center.y - st->g * (float)dt;
		if (impact_happened(s, st->ground))
		{
			spawn_shards(a, &a->scene, st, s);
			s->radius = 0.0f;
			st->phase = 1;
		}
		a->needs_redraw = 1;
		return ;
	}
	i = 0;
	while (i < st->count)
	{
		t_physics	*b;
		t_obj		*o;
		t_sphere	*s;

		b = &st->shards[i];
		if (b->active)
			phys_step(b, (float)dt, st->g, st->ground,
				st->bounce, st->fric);
		o = (t_obj *)b->obj_ptr;
		if (o)
		{
			s = (t_sphere *)o->ptr;
			if (s)
				s->center = b->pos;
		}
		i++;
	}
	a->needs_redraw = 1;
}
