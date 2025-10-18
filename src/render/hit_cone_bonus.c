/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:19:46 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/18 11:56:23 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

/* float-dot sebagai pembungkus dot_product(double) */
static float	vdot(t_vec3 a, t_vec3 b)
{
	return ((float)dot_product(a, b));
}

/* proyeksi ke sumbu (axis asumsi ter-norm), serta komponennya yang tegak lurus */
static t_vec3	vproj(t_vec3 v, t_vec3 axis)
{
	return (vmul(axis, vdot(v, axis)));
}

static t_vec3	vrej(t_vec3 v, t_vec3 axis)
{
	return (vsub(v, vproj(v, axis)));
}

/* kuadratik kerucut tak-terbatas (double-cone), k = tan(angle) */
static int	cone_solve(t_vec3 rdp, t_vec3 ocp, float dv, float ov, float k,
		float *t0, float *t1)
{
	float	a;
	float	b;
	float	c;
	float	d;
	float	sq;

	a = vdot(rdp, rdp) - (k * k) * (dv * dv);
	b = 2.0f * (vdot(rdp, ocp) - (k * k) * dv * ov);
	c = vdot(ocp, ocp) - (k * k) * (ov * ov);
	d = b * b - 4.0f * a * c;
	if (d < 0.0f || a == 0.0f)
		return (0);
	sq = sqrtf(d);
	*t0 = (-b - sq) / (2.0f * a);
	*t1 = (-b + sq) / (2.0f * a);
	return (1);
}

/* klip tinggi simetris: |pos sepanjang sumbu| <= height/2 */
static int	cone_clip_height(t_cone *co, t_vec3 axis, t_vec3 p)
{
	float	pos;

	pos = vdot(vsub(p, co->center), axis);
	if (pos < -co->height * 0.5f)
		return (0);
	if (pos > co->height * 0.5f)
		return (0);
	return (1);
}

/* normal sisi kerucut (tanpa caps) */
static t_vec3	cone_normal(t_cone *co, t_vec3 axis, t_vec3 p, float k)
{
	t_vec3	from_c;
	t_vec3	radial;
	float	lenr;
	float	s;

	from_c = vsub(p, co->center);
	radial = vrej(from_c, axis);
	lenr = vdot(radial, vnorm(radial));
	s = sqrtf(1.0f + k * k);
	/* arah normal: radial - axis * (|radial| * k / s) */
	return (vnorm(vsub(radial, vmul(axis, (lenr * k) / s))));
}

/* === API utama: ≤4 argumen, pakai t_ray* sebagai "hit record" === */
int	hit_cone(t_cone *co, t_ray ray, float tmax, t_ray *rec)
{
	t_vec3	axis;
	t_vec3	oc;
	t_vec3	rdp;
	t_vec3	ocp;
	float	k;
	float	dv;
	float	ov;
	float	t0;
	float	t1;
	float	t;
	t_vec3	p;

	axis = vnorm(co->axis);
	k = tanf(co->angle);
	oc = vsub(ray.origin, co->center);
	dv = vdot(ray.direction, axis);
	ov = vdot(oc, axis);
	rdp = vrej(ray.direction, axis);
	ocp = vrej(oc, axis);
	if (!cone_solve(rdp, ocp, dv, ov, k, &t0, &t1))
		return (0);
	t = t0;
	if (t < EPS)
		t = t1;
	if (t < EPS || t > tmax)
		return (0);
	p = vadd(ray.origin, vmul(ray.direction, t));
	if (!cone_clip_height(co, axis, p))
		return (0);
	rec->t = t;
	rec->normal = cone_normal(co, axis, p, k);
	rec->material = co->material;
	return (1);
}