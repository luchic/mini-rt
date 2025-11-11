/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:17:24 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/27 15:51:03 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_minirt.h"

/* ============================ tracing ============================ */

static int	try_hit_node(t_obj *node, t_ray r, float tmax, t_ray *hit_out)
{
	float		t;
	t_vec3		n;
	t_ray		rec;
	t_material	m;
	int			ok;

	ok = 0;
	if (node->type == OBJ_SPHERE)
		ok = hit_sphere((t_sphere *)node->ptr, r, tmax, &t, &n, &m);
	else if (node->type == OBJ_PLANE)
		ok = hit_plane((t_plane *)node->ptr, r, tmax, &t, &n, &m);
	else if (node->type == OBJ_CYLINDER)
		ok = hit_cylinder((t_cylinder *)node->ptr, r, tmax, &rec);
	else if (node->type == OBJ_CONE)
		ok = hit_cone((t_cone *)node->ptr, r, tmax, &rec);
	if (!ok)
		return (0);
	hit_out->t = t;
	hit_out->normal = n;
	hit_out->material = m;
	return (1);
}

static int	hit_all(t_scene *sc, t_ray r, t_ray *hit_out)
{
	t_obj	*it;
	float	best_t;
	t_ray	cur;
	int		any;

	it = sc->objs;
	best_t = TMAX;
	any = 0;
	while (it)
	{
		if (try_hit_node(it, r, best_t, &cur))
		{
			any = 1;
			best_t = cur.t;
			*hit_out = cur;
		}
		it = it->next;
	}
	return (any);
}

int	trace_ray(t_scene *sc, t_ray r, t_rgb *col_out)
{
	t_ray	hit_r;
	t_vec3	hit_p;
	t_ray	view_r;

	if (!hit_all(sc, r, &hit_r))
		return (0);
	hit_p = vadd(r.origin, vmul(r.direction, hit_r.t));
	view_r = ray(hit_p, vmul(r.direction, -1.0f));
	*col_out = shade(sc, view_r, hit_r.normal, &hit_r.material);
	return (1);
}

/* ========================= camera & render ======================= */

static void	build_cam_basis(t_camera *c)
{
	t_vec3	world_up;
	t_vec3	right;
	t_vec3	up;

	world_up = vec3(0.0f, 1.0f, 0.0f);
	right = vnorm(vcross_product(c->direction, world_up));
	up = vnorm(vcross_product(right, c->direction));
	c->right = right;
	c->up = up;
}

static t_ray	make_primary_ray(t_camera *c, int x, int y, int w, int h)
{
	float	aspect;
	float	fov_rad;
	float	scale;
	float	px;
	float	py;
	t_vec3	dir;

	aspect = (float)w / (float)h;
	fov_rad = c->fov_deg * PI_F / 180.0f;
	scale = tanf(fov_rad * 0.5f);
	px = (2.0f * ((x + 0.5f) / (float)w) - 1.0f) * aspect * scale;
	py = (1.0f - 2.0f * ((y + 0.5f) / (float)h)) * scale;
	dir = vnorm(vadd(vadd(vmul(c->right, px), vmul(c->up, py)), c->direction));
	return (ray(c->pos, dir));
}

static void	render_scanline(t_app *app, int y)
{
	int		x;
	t_ray	pr;
	t_rgb	color;

	x = 0;
	while (x < app->width)
	{
		pr = make_primary_ray(&app->scene.camera, x, y, app->width, app->height);
		if (trace_ray(&app->scene, pr, &color))
			image_put_px(&app->img, x, y, color);
		else
			image_put_px(&app->img, x, y, (t_rgb){0.0f, 0.0f, 0.0f});
		x++;
	}
}

void	render(t_app *app)
{
	int	y;

	build_cam_basis(&app->scene.camera);
	y = 0;
	while (y < app->height)
	{
		render_scanline(app, y);
		y++;
	}
	app->needs_redraw = 0;
}
