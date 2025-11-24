#include "ft_minirt.h"

static void	build_cam_basis(t_camera *c)
{
	t_vec3	forward;
	t_vec3	world_up;
	t_vec3	right;
	t_vec3	up;
	float	align;

	forward = vnorm(c->direction);
	world_up = vec3(0.0f, 1.0f, 0.0f);
	align = fabsf((float)dot_product(forward, world_up));
	if (align > 0.995f)
		world_up = vec3(0.0f, 0.0f, 1.0f);
	right = vnorm(vcross_product(forward, world_up));
	up = vnorm(vcross_product(right, forward));
	c->direction = forward;
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

static t_ray	make_primary_ray(t_camera *camera, float x,
	float y, t_render_context context)
{
	float	px;
	float	py;

	px = (2.0f * ((x + 0.5f) / (float)WIN_W) - 1.0f)
		* context.aspect * context.scale;
	py = (1.0f - 2.0f * ((y + 0.5f) / (float)WIN_H)) * context.scale;
	return (primary_ray(camera, px, py));
}


static void	render_scanline(t_app *app, int y)
{
	int					x;
	t_ray				pr;
	t_rgb				color;

	x = 0;
	while (x < app->width)
	{
		pr = make_primary_ray(&app->scene.camera, x, y, app->render_ctx);
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
