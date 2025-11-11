/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:22:12 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/27 14:34:30 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

int	hit_sphere(t_sphere *sp, t_ray ray_in, float tmax, float *t_hit_out, t_vec3 *normal_out, t_material *mat_out)
{
	t_vec3 offset_center = vsub(ray_in.origin, sp->center);
	float a_coef = dot_product(ray_in.direction, ray_in.direction);
	float b_coef = 2.0f * dot_product(offset_center, ray_in.direction);
	float c_coef = dot_product(offset_center, offset_center) - sp->radius * sp->radius;
	float discriminant = b_coef*b_coef - 4*a_coef*c_coef;
	float t_near, t_far, sqrt_disc;

	if (discriminant < 0) return (0);
	sqrt_disc = sqrtf(discriminant);
	t_near = (-b_coef - sqrt_disc) / (2.0f * a_coef);
	t_far  = (-b_coef + sqrt_disc) / (2.0f * a_coef);
	if (t_near < EPS) t_near = t_far;
	if (t_near < EPS || t_near > tmax) return (0);

	*t_hit_out = t_near;
	*normal_out = vnorm(vsub(vadd(ray_in.origin, vmul(ray_in.direction, *t_hit_out)), sp->center));
	mat_out->color    = sp->material.color;
	mat_out->checker  = sp->material.checker;
	mat_out->specular = sp->material.specular;
	mat_out->sp_exp   = sp->material.sp_exp;
	mat_out->bump     = sp->material.bump;
	return (1);
}
