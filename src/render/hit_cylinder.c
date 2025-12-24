/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:20:20 by yyudi             #+#    #+#             */
/*   Updated: 2025/12/24 13:51:00 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

/* selesaikan kuadratik untuk sisi tabung (tanpa tutup/caps) */
static int	cy_solve(t_vec3 rdp, t_vec3 ocp, float radius, double x[2])
{
	float	a;
	float	b;
	float	c;

	a = dot_product(rdp, rdp);
	b = 2.0f * dot_product(rdp, ocp);
	c = dot_product(ocp, ocp) - radius * radius;
	return (solve_quadratic(a, b, c, x));
}

/* cek posisi sepanjang sumbu: |pos| <= height/2 */
static int	cy_clip(t_cylinder *cy, t_vec3 axis, t_ray r, float t)
{
	t_vec3	p;
	float	pos;

	p = vadd(r.origin, vmul(r.direction, t));
	pos = dot_product(vsub(p, cy->center), axis);
	if (pos < -cy->height * 0.5f)
		return (0);
	if (pos > cy->height * 0.5f)
		return (0);
	return (1);
}

/* normal sisi: normalisasi komponen tegak lurus sumbu */
static t_vec3	cy_normal(t_cylinder *cy, t_vec3 axis, t_ray r, float t)
{
	t_vec3	p;
	t_vec3	perp;

	p = vadd(r.origin, vmul(r.direction, t));
	perp = vec3_reject_from_axis(vsub(p, cy->center), axis);
	return (vnorm(perp));
}

static int	hit_cap_setup(t_hit_context *ctx, t_ray ray,
	float *t, float *denom)
{
	*denom = dot_product(ctx->axis, ray.direction);
	if (fabsf(*denom) < EPS)
		return (0);
	*t = dot_product(vsub(ctx->cap_center, ray.origin), ctx->axis) / *denom;
	return (1);
}

static int	hit_cap(t_hit_context *ctx, t_ray ray, t_ray *rec)
{
	float	denom;
	float	t;
	t_vec3	p;
	t_vec3	to_p;
	float	dist_sq;

	if (!hit_cap_setup(ctx, ray, &t, &denom))
		return (0);
	if (t < EPS || t > ctx->tmax)
		return (0);
	p = vadd(ray.origin, vmul(ray.direction, t));
	to_p = vsub(p, ctx->cap_center);
	dist_sq = dot_product(to_p, to_p);
	if (dist_sq > ctx->cylinder->radius * ctx->cylinder->radius)
		return (0);
	rec->t = t;
	rec->origin = p;
	if (denom > 0)
		rec->normal = vmul(ctx->axis, -1.0f);
	else
		rec->normal = ctx->axis;
	rec->material = ctx->cylinder->material;
	rec->type = OBJ_CYLINDER;
	rec->local_p = vsub(p, ctx->cylinder->center);
	return (1);
}

static int	check_cylinder_side(t_hit_context *ctx,
	t_ray ray, double *x, t_ray *rec)
{
	if (!cy_solve(ctx->rdp, ctx->ocp, ctx->cylinder->radius, x))
		return (0);
	if (x[0] < EPS)
		x[0] = x[1];
	if (x[0] < EPS || x[0] > ctx->tmax)
		return (0);
	if (!cy_clip(ctx->cylinder, ctx->axis, ray, x[0]))
		return (0);
	rec->t = x[0];
	rec->origin = vadd(ray.origin, vmul(ray.direction, rec->t));
	rec->normal = cy_normal(ctx->cylinder, ctx->axis, ray, rec->t);
	rec->material = ctx->cylinder->material;
	rec->type = OBJ_CYLINDER;
	rec->local_p = vsub(rec->origin, ctx->cylinder->center);
	ctx->tmax = rec->t;
	return (1);
}

static void	check_cylinder_caps(t_hit_context *ctx,
		t_ray ray, t_ray *rec, int *hit_any)
{
	t_ray	cap_rec;
	int		hit_top;
	int		hit_bot;

	ctx->cap_center = vadd(ctx->cylinder->center,
			vmul(ctx->axis, -ctx->cylinder->height * 0.5f));
	hit_top = hit_cap(ctx, ray, &cap_rec);
	if (hit_top && cap_rec.t < ctx->tmax)
	{
		*rec = cap_rec;
		ctx->tmax = rec->t;
		*hit_any = 1;
	}
	ctx->cap_center = vadd(ctx->cylinder->center,
			vmul(ctx->axis, ctx->cylinder->height * 0.5f));
	hit_bot = hit_cap(ctx, ray, &cap_rec);
	if (hit_bot && cap_rec.t < ctx->tmax)
	{
		*rec = cap_rec;
		*hit_any = 1;
	}
}

int	hit_cylinder(t_cylinder *cy, t_ray ray, float tmax, t_ray *rec)
{
	t_hit_context	context;
	double			x[2];
	int				hit_any;

	context.cylinder = cy;
	context.tmax = tmax;
	context.axis = vnorm(context.cylinder->axis);
	context.oc = vsub(ray.origin, context.cylinder->center);
	context.rdp = vec3_reject_from_axis(ray.direction, context.axis);
	context.ocp = vec3_reject_from_axis(context.oc, context.axis);
	hit_any = check_cylinder_side(&context, ray, x, rec);
	check_cylinder_caps(&context, ray, rec, &hit_any);
	return (hit_any);
}
