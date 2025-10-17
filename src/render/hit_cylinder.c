/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:20:20 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/17 12:20:21 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_v3	reject(t_v3 v, t_v3 axis){ return (vsub(v, vmul(axis, vdot(v, axis)))); }

int	hit_cylinder(t_cyl *cy, t_ray ray_in, float tmax, float *t_hit_out, t_v3 *normal_out, t_mat *mat_out)
{
	t_v3  axis = cy->a;
	t_v3  oc = vsub(ray_in.o, cy->c);
	t_v3  rd_perp = reject(ray_in.d, axis);
	t_v3  oc_perp = reject(oc, axis);
	float a = vdot(rd_perp, rd_perp);
	float b = 2.0f * vdot(rd_perp, oc_perp);
	float c = vdot(oc_perp, oc_perp) - cy->r * cy->r;
	float discriminant = b*b - 4*a*c;
	float t0, t1, sqrt_disc, t_candidate;
	float axis_pos;

	if (discriminant < 0) return (0);
	sqrt_disc = sqrtf(discriminant);
	t0 = (-b - sqrt_disc) / (2.0f * a);
	t1 = (-b + sqrt_disc) / (2.0f * a);
	t_candidate = t0;
	if (t_candidate < EPS) t_candidate = t1;
	if (t_candidate < EPS || t_candidate > tmax) return (0);
	axis_pos = vdot(vadd(oc, vmul(ray_in.d, t_candidate)), axis);
	if (axis_pos < -cy->h * 0.5f || axis_pos > cy->h * 0.5f) return (0);

	*t_hit_out = t_candidate;
	*normal_out = vnorm(reject(vsub(vadd(ray_in.o, vmul(ray_in.d, *t_hit_out)), cy->c), axis));
	mat_out->color = cy->m.color;
	mat_out->checker = cy->m.checker;
	mat_out->specular = cy->m.specular;
	mat_out->sp_exp = cy->m.sp_exp;
	mat_out->bump = cy->m.bump;
	return (1);
}
