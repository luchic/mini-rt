/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:20:20 by yyudi             #+#    #+#             */
/*   Updated: 2025/12/24 13:02:58 by yyudi            ###   ########.fr       */
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

/* hit cap (tutup/disk) pada posisi tertentu sepanjang axis */
static int	hit_cap_setup(t_ray ray, t_vec3 axis, t_vec3 cap_center,
	float *t, float *denom)
{
	*denom = dot_product(axis, ray.direction);
	if (fabsf(*denom) < EPS)
		return (0);
	*t = dot_product(vsub(cap_center, ray.origin), axis) / *denom;
	return (1);
}

static int	hit_cap(t_cylinder *cy, t_vec3 axis, t_vec3 cap_center,
	t_ray ray, float tmax, t_ray *rec)
{
	float	denom;
	float	t;
	t_vec3	p;
	t_vec3	to_p;
	float	dist_sq;

	if (!hit_cap_setup(ray, axis, cap_center, &t, &denom))
		return (0);
	if (t < EPS || t > tmax)
		return (0);
	p = vadd(ray.origin, vmul(ray.direction, t));
	to_p = vsub(p, cap_center);
	dist_sq = dot_product(to_p, to_p);
	if (dist_sq > cy->radius * cy->radius)
		return (0);
	rec->t = t;
	rec->origin = p;
	if (denom > 0)
		rec->normal = vmul(axis, -1.0f);
	else
		rec->normal = axis;
	rec->material = cy->material;
	rec->type = OBJ_CYLINDER;
	rec->local_p = vsub(p, cy->center);
	return (1);
}

static int	check_cylinder_side(t_cylinder *cy, t_hit_context ctx,
	t_ray ray, double *x, t_ray *rec, float *tmax)
{
	if (!cy_solve(ctx.rdp, ctx.ocp, cy->radius, x))
		return (0);
	if (x[0] < EPS)
		x[0] = x[1];
	if (x[0] < EPS || x[0] > *tmax)
		return (0);
	if (!cy_clip(cy, ctx.axis, ray, x[0]))
		return (0);
	rec->t = x[0];
	rec->origin = vadd(ray.origin, vmul(ray.direction, rec->t));
	rec->normal = cy_normal(cy, ctx.axis, ray, rec->t);
	rec->material = cy->material;
	rec->type = OBJ_CYLINDER;
	rec->local_p = vsub(rec->origin, cy->center);
	*tmax = rec->t;
	return (1);
}

static void	check_cylinder_caps(t_cylinder *cy, t_hit_context ctx,
	t_ray ray, t_ray *rec, float *tmax, int *hit_any)
{
	t_ray	cap_rec;
	int		hit_top;
	int		hit_bot;

	hit_top = hit_cap(cy, ctx.axis,
			vadd(cy->center, vmul(ctx.axis, cy->height * 0.5f)),
			ray, *tmax, &cap_rec);
	if (hit_top && cap_rec.t < *tmax)
	{
		*rec = cap_rec;
		*tmax = rec->t;
		*hit_any = 1;
	}
	hit_bot = hit_cap(cy, ctx.axis,
			vadd(cy->center, vmul(ctx.axis, -cy->height * 0.5f)),
			ray, *tmax, &cap_rec);
	if (hit_bot && cap_rec.t < *tmax)
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

	context.axis = vnorm(cy->axis);
	context.oc = vsub(ray.origin, cy->center);
	context.rdp = vec3_reject_from_axis(ray.direction, context.axis);
	context.ocp = vec3_reject_from_axis(context.oc, context.axis);
	hit_any = check_cylinder_side(cy, context, ray, x, rec, &tmax);
	check_cylinder_caps(cy, context, ray, rec, &tmax, &hit_any);
	return (hit_any);
}
