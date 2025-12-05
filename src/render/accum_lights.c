#include "ft_minirt.h"

/* ---- helper: diffuse term ---------------------------------------------- */
static t_rgb	diffuse_rgb(t_rgb lc, t_material *m, double nd)
{
	t_rgb	diff;

	diff = rgb_mod(m->color, lc);
	return (rgb_mul(diff, (float)nd));
}

/* ---- helper: specular term --------------------------------------------- */
static t_rgb	specular_rgb(t_vec3 n, t_vec3 ldir, t_ray hv, t_rgb lc)
{
	t_rgb	sp;

	sp = specular_bonus(n, ldir, vnorm(hv.direction), &hv.material);
	return (rgb_mod(lc, sp));
}

/* ---- helper: hitung dir & jarak ke lampu (≤4 arg) ---------------------- */
static float	make_dir_and_dist(t_vec3 *out_dir, t_vec3 from, t_vec3 to)
{
	t_vec3	v;
	float	d;

	v = vsub(to, from);
	d = vlen(v);
	*out_dir = v;
	if (d > EPS)
		*out_dir = vdivv(v, d);
	return (d);
}

static t_rgb	accum_light_once(t_scene *sc, t_light *L, t_ray hv, t_vec3 n)
{
	t_vec3	dir;
	float	dist;
	double	nd;
	t_rgb	lc;
	t_rgb	sum;

	sum.red = 0.0f;
	sum.green = 0.0f;
	sum.blue = 0.0f;
	dist = make_dir_and_dist(&dir, hv.origin, L->pos);
	if (!in_shadow(sc, hv.origin, dir, dist))
	{
		nd = dot_product(n, dir);
		if (nd > 0.0)
		{
			lc = rgb_mul(L->color, L->br);
			sum = rgb_add(sum, diffuse_rgb(lc, &hv.material, nd));
			sum = rgb_add(sum, specular_rgb(n, dir, hv, lc));
		}
	}
	return (sum);
}

/* ---- loop semua lampu --------------------------------------------------- */
t_rgb	accum_lights(t_scene *sc, t_ray hv, t_vec3 n)
{
	t_light	*it;
	t_rgb	sum;

	sum.red = 0.0f;
	sum.green = 0.0f;
	sum.blue = 0.0f;
	it = sc->lights;
	while (it)
	{
		sum = rgb_add(sum, accum_light_once(sc, it, hv, n));
		it = it->next;
	}
	return (sum);
}
