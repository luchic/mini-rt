/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 14:30:11 by yyudi             #+#    #+#             */
/*   Updated: 2025/12/24 14:46:58 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static int	cone_cap_setup(t_cap_ctx cap, t_ray ray,
	float *distance, float *denom)
{
	*denom = dot_product(cap.axis, ray.direction);
	if (fabsf(*denom) < EPS)
		return (0);
	*distance = dot_product(vsub(cap.center, ray.origin), cap.axis) / *denom;
	return (1);
}

static int	hit_cone_cap(t_cone *co, t_cap_ctx cap, t_ray ray, t_ray *rec)
{
	float	denom;
	float	distance;
	t_vec3	hit_p;
	float	dist_sq;

	if (!cone_cap_setup(cap, ray, &distance, &denom))
		return (0);
	if (distance < EPS || distance > *(cap.tmax))
		return (0);
	hit_p = vadd(ray.origin, vmul(ray.direction, distance));
	dist_sq = dot_product(vsub(hit_p, cap.center), vsub(hit_p, cap.center));
	if (dist_sq > cap.radius * cap.radius)
		return (0);
	rec->t = distance;
	rec->origin = hit_p;
	*(cap.tmax) = distance;
	if (denom > 0)
		rec->normal = vmul(cap.axis, -1.0f);
	else
		rec->normal = cap.axis;
	rec->material = co->material;
	rec->type = OBJ_CONE;
	rec->local_p = vsub(hit_p, co->center);
	return (1);
}

int	hit_cone_side(t_cone *co, t_hit_context *ctx,
	t_ray ray, t_ray *rec)
{
	double	roots[2];
	float	distance;
	t_vec3	hit_p;

	if (!cone_solve(*ctx, roots))
		return (0);
	distance = roots[0];
	if (distance < EPS)
		distance = roots[1];
	if (distance < EPS || distance > ctx->tmax)
		return (0);
	hit_p = vadd(ray.origin, vmul(ray.direction, distance));
	if (!cone_clip_height(co, ctx->axis, hit_p))
		return (0);
	rec->origin = hit_p;
	rec->t = distance;
	rec->type = OBJ_CONE;
	rec->normal = cone_normal(co, ctx->axis, hit_p, ctx->k);
	rec->local_p = vsub(hit_p, co->center);
	rec->material = co->material;
	ctx->tmax = distance;
	return (1);
}

int	check_cone_caps(t_cone *co, t_hit_context *ctx,
	t_ray ray, t_ray *rec)
{
	t_cap_ctx	cap;
	t_ray		cap_rec;
	int			hit_any;

	cap.axis = ctx->axis;
	cap.radius = fabsf(co->height * 0.5f * ctx->k);
	cap.tmax = &(ctx->tmax);
	cap.center = vadd(co->center, vmul(cap.axis, co->height * 0.5f));
	hit_any = 0;
	if (hit_cone_cap(co, cap, ray, &cap_rec))
	{
		*rec = cap_rec;
		hit_any = 1;
	}
	cap.center = vadd(co->center, vmul(cap.axis, -co->height * 0.5f));
	if (hit_cone_cap(co, cap, ray, &cap_rec))
	{
		*rec = cap_rec;
		hit_any = 1;
	}
	return (hit_any);
}
