/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:19:46 by yyudi             #+#    #+#             */
/*   Updated: 2025/12/24 14:46:48 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

int	cone_solve(t_hit_context context, double x[2])
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

int	cone_clip_height(t_cone *co, t_vec3 axis, t_vec3 hit_point)
{
	float	axis_pos;

	axis_pos = dot_product(vsub(hit_point, co->center), axis);
	if (axis_pos < -co->height * 0.5f)
		return (0);
	if (axis_pos > co->height * 0.5f)
		return (0);
	return (1);
}

t_vec3	cone_normal(t_cone *co, t_vec3 axis, t_vec3 hit_point, float k)
{
	t_vec3	from_center;
	t_vec3	radial;
	float	radial_len;
	float	normal_scale;

	from_center = vsub(hit_point, co->center);
	radial = vec3_reject_from_axis(from_center, axis);
	radial_len = dot_product(radial, vnorm(radial));
	normal_scale = sqrtf(1.0f + k * k);
	return (vnorm(vsub(radial, vmul(axis, (radial_len * k) / normal_scale))));
}

int	hit_cone(t_cone *co, t_ray ray, float tmax, t_ray *rec)
{
	t_hit_context	context;
	int				hit_any;

	context.axis = vnorm(co->axis);
	context.k = tanf(co->angle);
	context.oc = vsub(ray.origin, co->center);
	context.dv = dot_product(ray.direction, context.axis);
	context.ov = dot_product(context.oc, context.axis);
	context.rdp = vec3_reject_from_axis(ray.direction, context.axis);
	context.ocp = vec3_reject_from_axis(context.oc, context.axis);
	context.tmax = tmax;
	hit_any = hit_cone_side(co, &context, ray, rec);
	if (check_cone_caps(co, &context, ray, rec))
		hit_any = 1;
	return (hit_any);
}
