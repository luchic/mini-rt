/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:17:24 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/17 17:22:47 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static int	hit_all(t_scene *sc, t_ray ray_in, float *tmin_out, t_vec3 *normal_out, t_material *mat_out)
{
	t_obj  *node = sc->objs;
	float   t_candidate; 
	t_vec3    normal_candidate; 
	t_material   mat_candidate;
	int     any_hit = 0;
	float   best_t = TMAX;

	while (node)
	{
		if (node->type == OBJ_SPHERE && hit_sphere((t_sphere*)node->ptr, ray_in, best_t, &t_candidate, &normal_candidate, &mat_candidate)) { any_hit=1; best_t=t_candidate; *normal_out=normal_candidate; *mat_out=mat_candidate; }
		if (node->type == OBJ_PLANE  && hit_plane((t_plane*)node->ptr,  ray_in, best_t, &t_candidate, &normal_candidate, &mat_candidate)) { any_hit=1; best_t=t_candidate; *normal_out=normal_candidate; *mat_out=mat_candidate; }
		if (node->type == OBJ_CYL    && hit_cylinder((t_cylinder*)node->ptr, ray_in, best_t, &t_candidate, &normal_candidate, &mat_candidate)) { any_hit=1; best_t=t_candidate; *normal_out=normal_candidate; *mat_out=mat_candidate; }
		if (node->type == OBJ_CONE   && hit_cone((t_cone*)node->ptr,   ray_in, best_t, &t_candidate, &normal_candidate, &mat_candidate)) { any_hit=1; best_t=t_candidate; *normal_out=normal_candidate; *mat_out=mat_candidate; }
		node = node->next;
	}
	if (any_hit) *tmin_out = best_t;
	return (any_hit);
}

int	trace_ray(t_scene *sc, t_ray ray_in, t_rgb *color_out)
{
	float		t_hit; 
	t_vec3		surface_normal; 
	t_material	hit_material;
	t_vec3 		hit_point;

	if (!hit_all(sc, ray_in, &t_hit, &surface_normal, &hit_material))
		return (0);
	hit_point = vadd(ray_in.o, vmul(ray_in.d, t_hit));
	*color_out = shade(sc, hit_point, surface_normal,
			&hit_material, vmul(ray_in.d, -1.0f));
	return (1);
}

void	render(t_app *app)
{
	int x, y;
	float aspect = (float)app->win_w / (float)app->win_h;
	float fov_rad = app->sc.cam.fov_deg * PI_F / 180.0f;
	float image_plane_scale = tanf(fov_rad * 0.5f);

	camera_build(&app->sc.cam);
	y = 0;
	while (y < app->win_h)
	{
		x = 0;
		while (x < app->win_w)
		{
			float ndc_x = (2.0f * ((x + 0.5f) / (float)app->win_w) - 1.0f) * aspect * image_plane_scale;
			float ndc_y = (1.0f - 2.0f * ((y + 0.5f) / (float)app->win_h)) * image_plane_scale;
			t_vec3 dir = vnorm(vadd(vadd(vmul(app->sc.cam.right, ndc_x),
			                           vmul(app->sc.cam.up, ndc_y)),
			                      app->sc.cam.dir));
			t_ray primary = ray(app->sc.cam.pos, dir);
			t_rgb pixel_color;

			if (trace_ray(&app->sc, primary, &pixel_color))
				image_put_px(&app->img, x, y, pixel_color);
			else
				image_put_px(&app->img, x, y, (t_rgb){0.0f, 0.0f, 0.0f});
			x++;
		}
		y++;
	}
	app->needs_redraw = 0;
}
