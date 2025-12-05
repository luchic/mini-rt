/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:22:12 by yyudi             #+#    #+#             */
/*   Updated: 2025/11/12 11:10:19 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static float	get_near_hit(t_sphere *sphere, t_ray ray_in, float *near)
{
	t_vec3	offset_center;
	float	a_coef;
	float	b_coef;
	float	c_coef;
	double	x[2];

	offset_center = vsub(ray_in.origin, sphere->center);
	a_coef = dot_product(ray_in.direction, ray_in.direction);
	b_coef = 2.0f * dot_product(offset_center, ray_in.direction);
	c_coef = dot_product(offset_center, offset_center) - sphere->radius
		* sphere->radius;
	if (!solve_quadratic(a_coef, b_coef, c_coef, x))
		return (0);
	*near = (float)x[0];
	return (1);
}

int	hit_sphere(t_sphere *sp, t_ray ray_in, t_ray *hit_out)
{
	float		t_near;
	t_material	material;

	if (!get_near_hit(sp, ray_in, &t_near))
		return (0);
	material.color = sp->material.color;
	material.checker = sp->material.checker;
	material.specular = sp->material.specular;
	material.sp_exp = sp->material.sp_exp;
	material.bump = sp->material.bump;
	hit_out->t = t_near;
	hit_out->normal = vnorm(vsub(vadd(ray_in.origin, vmul(ray_in.direction,
						t_near)), sp->center));
	hit_out->material = material;
	return (1);
}
