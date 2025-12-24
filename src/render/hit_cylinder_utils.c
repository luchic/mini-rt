/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:52:58 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 13:53:21 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

/* selesaikan kuadratik untuk sisi tabung (tanpa tutup/caps) */
int	cy_solve(t_vec3 rdp, t_vec3 ocp, float radius, double x[2])
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
int	cy_clip(t_cylinder *cy, t_vec3 axis, t_ray r, float t)
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
t_vec3	cy_normal(t_cylinder *cy, t_vec3 axis, t_ray r, float t)
{
	t_vec3	p;
	t_vec3	perp;

	p = vadd(r.origin, vmul(r.direction, t));
	perp = vec3_reject_from_axis(vsub(p, cy->center), axis);
	return (vnorm(perp));
}

int	hit_cap_setup(t_hit_context *ctx, t_ray ray,
	float *t, float *denom)
{
	*denom = dot_product(ctx->axis, ray.direction);
	if (fabsf(*denom) < EPS)
		return (0);
	*t = dot_product(vsub(ctx->cap_center, ray.origin), ctx->axis) / *denom;
	return (1);
}
