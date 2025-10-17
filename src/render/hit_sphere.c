/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:22:12 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/17 12:22:15 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	hit_sphere(t_sphere *sp, t_ray ray_in, float tmax, float *t_hit_out, t_v3 *normal_out, t_mat *mat_out)
{
	t_v3 offset_center = vsub(ray_in.o, sp->c);
	float a_coef = vdot(ray_in.d, ray_in.d);
	float b_coef = 2.0f * vdot(offset_center, ray_in.d);
	float c_coef = vdot(offset_center, offset_center) - sp->r * sp->r;
	float discriminant = b_coef*b_coef - 4*a_coef*c_coef;
	float t_near, t_far, sqrt_disc;

	if (discriminant < 0) return (0);
	sqrt_disc = sqrtf(discriminant);
	t_near = (-b_coef - sqrt_disc) / (2.0f * a_coef);
	t_far  = (-b_coef + sqrt_disc) / (2.0f * a_coef);
	if (t_near < EPS) t_near = t_far;
	if (t_near < EPS || t_near > tmax) return (0);

	*t_hit_out = t_near;
	*normal_out = vnorm(vsub(vadd(ray_in.o, vmul(ray_in.d, *t_hit_out)), sp->c));
	mat_out->color    = sp->m.color;
	mat_out->checker  = sp->m.checker;
	mat_out->specular = sp->m.specular;
	mat_out->sp_exp   = sp->m.sp_exp;
	mat_out->bump     = sp->m.bump;
	return (1);
}
