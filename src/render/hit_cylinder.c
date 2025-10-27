/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:20:20 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/18 11:53:42 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

/* util dot(float) agar ringkas */
static float	vdot(t_vec3 a, t_vec3 b)
{
	return ((float)dot_product(a, b));
}

/* proyeksi v ke sumbu 'axis'  (axis dianggap sudah ter-norm) */
static t_vec3	vproj(t_vec3 v, t_vec3 axis)
{
	t_vec3	out;

	out = vmul(axis, vdot(v, axis));
	return (out);
}

/* komponen tegak lurus sumbu: v - proj_axis(v) */
static t_vec3	vrej(t_vec3 v, t_vec3 axis)
{
	t_vec3	out;

	out = vsub(v, vproj(v, axis));
	return (out);
}

/* selesaikan kuadratik untuk sisi tabung (tanpa tutup/caps) */
static int	cy_solve(t_vec3 rdp, t_vec3 ocp, float *t0, float *t1)
{
	float	a;
	float	b;
	float	c;
	float	d;
	float	sq;

	a = vdot(rdp, rdp);
	b = 2.0f * vdot(rdp, ocp);
	c = vdot(ocp, ocp) - 0.0f;
	d = b * b - 4.0f * a * c;
	if (d < 0.0f || a == 0.0f)
		return (0);
	sq = sqrtf(d);
	*t0 = (-b - sq) / (2.0f * a);
	*t1 = (-b + sq) / (2.0f * a);
	return (1);
}

/* cek posisi sepanjang sumbu: |pos| <= height/2 */
static int	cy_clip(t_cylinder *cy, t_vec3 axis, t_ray r, float t)
{
	t_vec3	p;
	float	pos;

	p = vadd(r.origin, vmul(r.direction, t));
	pos = vdot(vsub(p, cy->center), axis);
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
	perp = vrej(vsub(p, cy->center), axis);
	return (vnorm(perp));
}

/* hit cylinder (tanpa caps), pakai t_ray* sebagai "hit record" */
int	hit_cylinder(t_cylinder *cy, t_ray ray, float tmax, t_ray *rec)
{
	t_vec3	axis;
	t_vec3	oc;
	t_vec3	rdp;
	t_vec3	ocp;
	float	t0;
	float	t1;

	axis = vnorm(cy->axis);
	oc = vsub(ray.origin, cy->center);
	rdp = vrej(ray.direction, axis);
	ocp = vrej(oc, axis);
	if (!cy_solve(rdp, ocp, &t0, &t1))
		return (0);
	if (t0 < EPS)
		t0 = t1;
	if (t0 < EPS || t0 > tmax)
		return (0);
	if (!cy_clip(cy, axis, ray, t0))
		return (0);
	rec->t = t0;
	rec->normal = cy_normal(cy, axis, ray, rec->t);
	rec->material = cy->material;
	return (1);
}
