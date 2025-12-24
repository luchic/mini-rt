/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accum_light_once.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:59:00 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 13:59:01 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static float	spotlight_factor(t_light *L, t_vec3 dir)
{
	float	cos_angle;
	float	spot_factor;

	if (L->type != LIGHT_SPOT)
		return (1.0f);
	cos_angle = -dot_product(dir, L->dir);
	if (cos_angle < L->cutoff_cos)
		return (0.0f);
	spot_factor = (cos_angle - L->cutoff_cos) / (1.0f - L->cutoff_cos);
	return (spot_factor * spot_factor);
}

t_rgb	accum_light_once(t_scene *sc, t_light *L, t_ray hv, t_vec3 n)
{
	t_light_once_ctx	ctx;

	ft_bzero(&ctx.sum, sizeof(ctx.sum));
	ctx.dist = make_dir_and_dist(&ctx.dir, hv.origin, L->pos);
	ctx.spot = spotlight_factor(L, ctx.dir);
	if (ctx.spot > EPS && !in_shadow(sc, hv.origin, ctx.dir, ctx.dist))
	{
		ctx.nd = dot_product(n, ctx.dir);
		if (ctx.nd > 0.0)
		{
			ctx.lc = rgb_mul(L->color, L->br * ctx.spot);
			ctx.sum = rgb_add(ctx.sum,
					diffuse_rgb(ctx.lc, &hv.material, ctx.nd));
			ctx.sum = rgb_add(ctx.sum, specular_rgb(n, ctx.dir, hv, ctx.lc));
		}
	}
	return (ctx.sum);
}
