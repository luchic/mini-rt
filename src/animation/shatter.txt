#include "ft_minirt.h"


static t_shfx *fx(void)
{
	static t_shfx st;
	return (&st);
}


static t_vec3 vproj_on_n(t_vec3 v, t_vec3 n)
{
	return vmul(n, dot_product(v, n));
}

static float plane_signed_dist(t_vec3 p, t_plane *pl)
{
	return dot_product(vsub(p, pl->position), pl->normal);
}

static void collide_sphere_plane(t_physics *b, t_plane *pl, float e, float mu)
{
	float  dist;
	t_vec3   n;
	t_vec3   vn;
	t_vec3   vt;

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
		b->vel = vadd(vmul(vn, -e), vmul(vt, (1.0f - mu)));
}

static void phys_step(t_physics *b, float dt, float g, t_plane *pl, float e, float mu)
{
	if (!b || !b->active)
		return ;
	b->vel.y = b->vel.y - g * dt;
	b->pos = vadd(b->pos, vmul(b->vel, dt));
	if (pl)
		collide_sphere_plane(b, pl, e, mu);
}


static t_obj *new_sphere_node(t_scene *sc, t_vec3 c, float r, t_material m)
{
	t_sphere *s;
	t_obj    *o;

	if (!sc)
		return (0);
	s = (t_sphere *)emalloc(sizeof(*s));
	s->center = c; s->radius = r; s->material = m;
	o = (t_obj *)emalloc(sizeof(*o));
	o->type = OBJ_SPHERE; o->ptr = s; o->next = sc->objs;
	sc->objs = o;
	return (o);
}

t_obj *find_first(t_scene *sc, t_objtype type)
{
	t_obj *o;

	o = sc ? sc->objs : 0;
	while (o)
	{
		if (o->type == type)
			return (o);
		o = o->next;
	}
	return (0);
}

static t_plane *find_ground(t_scene *sc)
{
	t_obj *o;

	o = find_first(sc, OBJ_PLANE);
	return (o ? (t_plane *)o->ptr : 0);
}

static void spawn_shards(t_app *app, t_scene *sc, t_shfx *st, t_sphere *big)
{
	int   i;
	int   n;
	t_material m;

	if (!sc || !st || !big)
		return ;
	n = 5;
	if (n > (int)(sizeof(st->shards) / sizeof(st->shards[0])))
		n = sizeof(st->shards) / sizeof(st->shards[0]);
	m = big->material;
	i = 0;
	while (i < n)
	{
		float a  = 6.2831853f * rng_random01(app);
		float u  = 0.2f + 0.8f * rng_random01(app);
		t_vec3 dir = vnorm(vec3(cosf(a), 0.2f + u, sinf(a)));
		float v0 = 2.5f + 2.0f * rng_random01(app);
		t_vec3 p   = vadd(big->center, vmul(dir, big->radius * 0.3f));
		st->shards[i].obj_ptr = new_sphere_node(sc, p, big->radius * 0.18f, m);
		st->shards[i].pos = p;
		st->shards[i].vel = vmul(dir, v0);
		st->shards[i].radius   = big->radius * 0.18f;
		st->shards[i].active = 1;
		i++;
	}
	st->count = n;
}

static int impact_happened(t_sphere *big, t_plane *pl)
{
	if (!big)
		return (0);
	if (pl)
		return (plane_signed_dist(big->center, pl) <= big->radius);
	return (big->center.y <= big->radius);
}

/* ====== API ====== */
void	shfx_trigger(t_app *a)
{
	t_shfx   *st;
	t_sphere *s;

	if (!a)
		return ;
	rng_seed(a, 0xC0FFEEu);
	a->last_ts = mlx_get_time();
	st = fx();
	st->enabled = 1;
	st->phase = 0;
	st->big_obj = find_first(&a->scene, OBJ_SPHERE);
	st->ground  = find_ground(&a->scene);
	st->g = 9.8f; st->bounce = 0.35f; st->fric = 0.10f; st->count = 0;
	if (!st->big_obj || !st->big_obj->ptr)
		return ;
	s = (t_sphere *)st->big_obj->ptr;
	if (s->center.y < s->radius + 0.1f)
		s->center.y = s->radius + 0.1f;
}

void	shfx_update(t_app *a, double now)
{
	t_shfx *st;
	double  dt;
	int     i;

	if (!a)
		return ;
	st = fx();
	if (!st->enabled)
		return ;
	dt = now - a->last_ts;
	if (dt < (1.0/60.0))
		return ;
	if (dt > 0.05)
		dt = 0.05;
	a->last_ts = now;
	if (!st->big_obj || !st->big_obj->ptr)
		return ;
	if (st->phase == 0)
	{
		t_sphere *s = (t_sphere *)st->big_obj->ptr;
		s->center.y = s->center.y - st->g * (float)dt;
		if (impact_happened(s, st->ground))
		{
			spawn_shards(a, &a->scene, st, s);
			s->radius = 0.0f; /* sembunyikan sphere besar */
			st->phase = 1;
		}
		a->needs_redraw = 1;
		return ;
	}
	i = 0;
	while (i < st->count)
	{
		t_physics *b = &st->shards[i];
		if (b->active)
			phys_step(b, (float)dt, st->g, st->ground, st->bounce, st->fric);
		if (b->obj_ptr)
		{
			t_obj    *o = (t_obj *)b->obj_ptr;
			t_sphere *s = (t_sphere *)o->ptr;
			if (s)
				s->center = b->pos;
		}
		i++;
	}
	a->needs_redraw = 1;
}
