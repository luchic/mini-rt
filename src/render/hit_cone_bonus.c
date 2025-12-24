/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:19:46 by yyudi             #+#    #+#             */
/*   Updated: 2025/12/24 14:01:02 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

// Perpendicular component (rejection from the axis)
static int	cone_solve(t_hit_context context, double x[2])
{
	float	a;
	float	b;
	float	c;

	a = dot_product(context.rdp, context.rdp)
		- (context.k * context.k) * (context.dv * context.dv);
	b = 2.0f * (dot_product(context.rdp, context.ocp)
			- (context.k * context.k) * context.dv * context.ov);
	c = dot_product(context.ocp, context.ocp)
		- (context.k * context.k) * (context.ov * context.ov);
	return (solve_quadratic(a, b, c, x));
}

/* Quadratic for an infinite (double) cone, k = tan(angle) */
static int	cone_clip_height(t_cone *co, t_vec3 axis, t_vec3 p)
{
	float	pos;

	pos = dot_product(vsub(p, co->center), axis);
	if (pos < -co->height * 0.5f)
		return (0);
	if (pos > co->height * 0.5f)
		return (0);
	return (1);
}

/* Symmetric height clipping: |position along the axis| <= height/2 */
static t_vec3	cone_normal(t_cone *co, t_vec3 axis, t_vec3 p, float k)
{
	t_vec3	from_c;
	t_vec3	radial;
	float	lenr;
	float	s;

	from_c = vsub(p, co->center);
	radial = vec3_reject_from_axis(from_c, axis);
	lenr = dot_product(radial, vnorm(radial));
	s = sqrtf(1.0f + k * k);
	return (vnorm(vsub(radial, vmul(axis, (lenr * k) / s))));
}

/* Symmetric height clipping: |position along the axis| <= height/2 */
int	hit_cone(t_cone *co, t_ray ray, float tmax, t_ray *rec)
{
	double				x[2];
	float				t;
	t_vec3				p;
	t_hit_context		context;

	context.axis = vnorm(co->axis);
	context.k = tanf(co->angle);
	context.oc = vsub(ray.origin, co->center);
	context.dv = dot_product(ray.direction, context.axis);
	context.ov = dot_product(context.oc, context.axis);
	context.rdp = vec3_reject_from_axis(ray.direction, context.axis);
	context.ocp = vec3_reject_from_axis(context.oc, context.axis);
	if (!cone_solve(context, x))
		return (0);
	t = x[0];
	if (t < EPS)
		t = x[1];
	if (t < EPS || t > tmax)
		return (0);
	p = vadd(ray.origin, vmul(ray.direction, t));
	if (!cone_clip_height(co, context.axis, p))
		return (0);
	return (rec->origin = p, rec->t = t, rec->type = OBJ_CONE,
		rec->normal = cone_normal(co, context.axis, p, context.k),
		rec->local_p = vsub(p, co->center), rec->material = co->material, 1);
}
