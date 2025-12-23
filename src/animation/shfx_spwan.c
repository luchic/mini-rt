#include "ft_minirt.h"

static t_obj	*new_sphere_node(t_scene *sc, t_vec3 c, float r, t_material m)
{
	t_sphere	*s;
	t_obj		*o;

	if (!sc)
		return (0);
	s = (t_sphere *)emalloc(sizeof(*s));
	s->center = c;
	s->radius = r;
	s->material = m;
	o = (t_obj *)emalloc(sizeof(*o));
	o->type = OBJ_SPHERE;
	o->ptr = s;
	o->next = sc->objs;
	sc->objs = o;
	return (o);
}

static void	init_shard(t_app *app, t_shfx *st,
			t_sphere *big, int idx)
{
	float	a;
	float	u;
	t_vec3	dir;
	float	v0;
	t_vec3	p;

	a = 6.2831853f * rng_random01(app);
	u = 0.2f + 0.8f * rng_random01(app);
	dir = vnorm(vec3(cosf(a), 0.2f + u, sinf(a)));
	v0 = 2.5f + 2.0f * rng_random01(app);
	p = vadd(big->center, vmul(dir, big->radius * 0.3f));
	st->shards[idx].obj_ptr = new_sphere_node(&app->scene,
			p, big->radius * 0.18f, big->material);
	st->shards[idx].pos = p;
	st->shards[idx].vel = vmul(dir, v0);
	st->shards[idx].radius = big->radius * 0.18f;
	st->shards[idx].active = 1;
}

void	spawn_shards(t_app *app, t_shfx *st, t_sphere *big)
{
	int	i;
	int	n;

	if (!st || !big)
		return ;
	n = 5;
	if (n > (int)(sizeof(st->shards) / sizeof(st->shards[0])))
		n = (int)(sizeof(st->shards) / sizeof(st->shards[0]));
	i = 0;
	while (i < n)
	{
		init_shard(app, st, big, i);
		i++;
	}
	st->count = n;
}
