/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:22:37 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/18 11:50:12 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

/* ---- bonus hooks (disediakan di modul bonus jika ada) ------------------- */
t_rgb		checker_bonus(t_vec3 p, t_rgb base);
t_vec3		bump_bonus(t_vec3 n, t_vec3 p, t_material *m);
t_rgb		specular_bonus(t_vec3 n, t_vec3 l, t_vec3 v, t_material *m);
int			in_shadow(t_scene *sc, t_vec3 p, t_vec3 to_l, float max_d);

/* ---- util warna --------------------------------------------------------- */
static t_rgb	rgb_add(t_rgb a, t_rgb b)
{
	t_rgb	out;

	out.red = a.red + b.red;
	out.green = a.green + b.green;
	out.blue = a.blue + b.blue;
	return (out);
}

static t_rgb	rgb_mul(t_rgb a, float k)
{
	t_rgb	out;

	out.red = a.red * k;
	out.green = a.green * k;
	out.blue = a.blue * k;
	return (out);
}

static t_rgb	rgb_mod(t_rgb a, t_rgb b)
{
	t_rgb	out;

	out.red = a.red * b.red;
	out.green = a.green * b.green;
	out.blue = a.blue * b.blue;
	return (out);
}

static t_rgb	rgb_clamp01(t_rgb c)
{
	t_rgb	out;

	out = c;
	if (out.red > 1.0f)
		out.red = 1.0f;
	if (out.green > 1.0f)
		out.green = 1.0f;
	if (out.blue > 1.0f)
		out.blue = 1.0f;
	if (out.red < 0.0f)
		out.red = 0.0f;
	if (out.green < 0.0f)
		out.green = 0.0f;
	if (out.blue < 0.0f)
		out.blue = 0.0f;
	return (out);
}

/* ---- efek permukaan (checker/bump) ------------------------------------- */
static void	apply_surface_effects(t_material *m, t_vec3 p, t_vec3 *n, t_rgb *base)
{
	if (m->checker)
		*base = checker_bonus(p, *base);
	if (m->bump)
		*n = bump_bonus(*n, p, m);
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

/* ---- kontribusi satu lampu (≤5 variabel, ≤25 baris) -------------------- */
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
static t_rgb	accum_lights(t_scene *sc, t_ray hv, t_vec3 n)
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

/* ---- entry point sesuai ft_minirt.h ------------------------------------ */
t_rgb	shade(t_scene *sc, t_ray hit_view, t_vec3 normal, t_material *mat)
{
	t_rgb	amb;
	t_rgb	out;
	t_ray	hv;
	t_vec3	n;

	hv = hit_view;
	hv.material = *mat;
	n = normal;

	apply_surface_effects(&hv.material, hv.origin, &n, &hv.material.color);
	amb = rgb_mul(sc->amb_color, sc->amb);
	out = rgb_add(amb, accum_lights(sc, hv, n));
	return (rgb_clamp01(out));
}