#include "ft_minirt.h"

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

static t_ray	primary_ray(t_camera *camera, float px, float py)
{
	t_vec3	direction;
	t_vec3	horizontal_offset;
	t_vec3	vertical_offset;
	t_vec3	tmp;

	horizontal_offset = vmul(camera->right, px);
	vertical_offset = vmul(camera->up, py);
	tmp = vadd(horizontal_offset, vertical_offset);
	tmp = vadd(tmp, camera->direction);
	direction = vnorm(tmp);
	return (ray(camera->pos, direction));
}

static t_ray	make_primary_ray(t_camera *camera, int coord[2], int w, int h)
{
	float	aspect;
	float	fov_rad;
	float	scale;
	float	px;
	float	py;

	aspect = (float)w / (float)h;
	fov_rad = camera->fov_deg * PI_F / 180.0f;
	scale = tanf(fov_rad * 0.5f);
	px = (2.0f * ((coord[0] + 0.5f) / (float)w) - 1.0f) * aspect * scale;
	py = (1.0f - 2.0f * ((coord[1] + 0.5f) / (float)h)) * scale;
	return (primary_ray(camera, px, py));
}

static void	render_scanline(t_app *app, int y)
{
	int		coord[2];
	t_ray	pr;
	t_rgb	color;

	coord[0] = 0;
	coord[1] = y;
	while (coord[0] < app->width)
	{
		pr = make_primary_ray(&app->scene.camera, coord, app->width,
				app->height);
		if (trace_ray(&app->scene, pr, &color))
			image_put_px(&app->img, coord[0], coord[1], color);
		else
			image_put_px(&app->img, coord[0],
				coord[1], (t_rgb){0.0f, 0.0f, 0.0f});
		coord[0]++;
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
