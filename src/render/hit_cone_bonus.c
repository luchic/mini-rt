/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:19:46 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/17 12:19:51 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#ifdef BONUS
static t_v3	reject(t_v3 v, t_v3 axis){ return (vsub(v, vmul(axis, vdot(v, axis)))); }

int	hit_cone(t_cone *co, t_ray ray_in, float tmax, float *t_hit_out, t_v3 *normal_out, t_mat *mat_out)
{
	float k = tanf(co->ang);
	t_v3  axis = co->a;
	t_v3  oc = vsub(ray_in.o, co->c);
	float dv = vdot(ray_in.d, axis);
	float ov = vdot(oc, axis);
	t_v3  rd_perp = reject(ray_in.d, axis);
	t_v3  oc_perp = reject(oc, axis);
	float A = vdot(rd_perp, rd_perp) - (k*k) * (dv*dv);
	float B = 2.0f * (vdot(rd_perp, oc_perp) - (k*k) * dv * ov);
	float C = vdot(oc_perp, oc_perp) - (k*k) * (ov*ov);
	float discriminant = B*B - 4*A*C;
	float t0, t1, sqrt_disc, t_hit, axis_pos;
	t_v3 hit_point, axis_from_center;

	if (discriminant < 0)
		return (0);
	sqrt_disc = sqrtf(discriminant);
	t0 = (-B - sqrt_disc) / (2.0f*A);
	t1 = (-B + sqrt_disc) / (2.0f*A);
	t_hit = t0;
	if (t_hit < EPS) t_hit = t1;
	if (t_hit < EPS || t_hit > tmax) return (0);
	hit_point = vadd(ray_in.o, vmul(ray_in.d, t_hit));
	axis_from_center = vsub(hit_point, co->c);
	axis_pos = vdot(axis_from_center, axis);
	if (axis_pos < -co->h * 0.5f || axis_pos > co->h * 0.5f) return (0);

	*t_hit_out = t_hit;
	{
		t_v3 radial = reject(axis_from_center, axis);
		float s = sqrtf(1.0f + k*k);
		t_v3 n_local = vnorm(vsub(radial, vmul(axis, vlen(radial) * k / s)));
		*normal_out = n_local;
	}
	mat_out->color = co->m.color;
	mat_out->checker = co->m.checker;
	mat_out->specular = co->m.specular;
	mat_out->sp_exp = co->m.sp_exp;
	mat_out->bump = co->m.bump;
	return (1);
}
#else
int	hit_cone(t_cone *co, t_ray r, float tmax, float *t, t_v3 *n, t_mat *m)
{ (void)co; (void)r; (void)tmax; (void)t; (void)n; (void)m; return (0); }
#endif
