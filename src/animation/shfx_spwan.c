#include "ft_minirt.h"

static t_obj	*new_sphere_node(t_scene *sc, t_vec3 c, float r, t_material m)
{
	t_sphere	*s;
	t_obj		*o;

	if (!sc)
		return (NULL);
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

void	spawn_shards(t_app *app, t_scene *sc, t_shfx *st, t_sphere *big)
{
	int			i;
	int			n;
	t_material	m;

	if (!sc || !st || !big)
		return ;
	n = 5;
	if (n > (int)(sizeof(st->shards) / sizeof(st->shards[0])))
		n = (int)(sizeof(st->shards) / sizeof(st->shards[0]));
	m = big->material;
	i = 0;
	while (i < n)
	{
		float	a = 6.2831853f * rng_random01(app);
		float	u = 0.2f + 0.8f * rng_random01(app);
		t_vec3	dir = vnorm(vec3(cosf(a), 0.2f + u, sinf(a)));
		float	v0 = 2.5f + 2.0f * rng_random01(app);
		t_vec3	p = vadd(big->center, vmul(dir, big->radius * 0.3f));
		st->shards[i].obj_ptr = new_sphere_node(sc, p, big->radius * 0.18f, m);
		st->shards[i].pos = p;
		st->shards[i].vel = vmul(dir, v0);
		st->shards[i].radius = big->radius * 0.18f;
		st->shards[i].active = 1;
		i++;
	}
	st->count = n;
}
