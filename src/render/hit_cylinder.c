/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:20:20 by yyudi             #+#    #+#             */
/*   Updated: 2025/12/22 15:43:27 by yyudi            ###   ########.fr       */
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

/* hit cylinder (tanpa caps), pakai t_ray* sebagai "hit record" */
int	hit_cylinder(t_cylinder *cy, t_ray ray, float tmax, t_ray *rec)
{
	t_hit_context	context;
	double			x[2];

	context.axis = vnorm(cy->axis);
	context.oc = vsub(ray.origin, cy->center);
	context.rdp = vec3_reject_from_axis(ray.direction, context.axis);
	context.ocp = vec3_reject_from_axis(context.oc, context.axis);
	if (!cy_solve(context.rdp, context.ocp, cy->radius, x))
		return (0);
	if (x[0] < EPS)
		x[0] = x[1];
	if (x[0] < EPS || x[0] > tmax)
		return (0);
	if (!cy_clip(cy, context.axis, ray, x[0]))
		return (0);
	rec->t = x[0];
	rec->normal = cy_normal(cy, context.axis, ray, rec->t);
	rec->material = cy->material;
	rec->type = OBJ_CYLINDER;
	rec->local_p = vsub(vadd(ray.origin, vmul(ray.direction, rec->t)), cy->center);
	return (1);
}
