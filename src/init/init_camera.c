#include "ft_minirt.h"

static t_vec3	choose_up(t_vec3 dir)
{
	t_vec3	up;

	up = vec3(0, 1, 0);
	if (fabsf(dir.y) > 0.99f)
		up = vec3(0, 0, 1);
	return (up);
}

void	camera_build(t_camera *camera)
{
	t_vec3	up;

	up = choose_up(camera->direction);
	camera->right = vnorm(vcross_product(camera->direction, up));
	camera->up = vnorm(vcross_product(camera->right, camera->direction));
}

void	init_camera_animation(t_app *app)
{
	if (app)
		app->animation.enabled = 0;
	// g_mode = LIGHT_NORMAL;
}