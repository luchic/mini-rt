#include "ft_minirt.h"

// static t_vec3	choose_up(t_vec3 dir)
// {
// 	t_vec3	up;

// 	up = vec3(0, 1, 0);
// 	if (fabsf(dir.y) > 0.99f)
// 		up = vec3(0, 0, 1);
// 	return (up);
// }

void	init_camera_animation(t_app *app)
{
	if (!app)
		return ;
	app->animation.enabled = 1;
	app->animation.speed = 0.6f;
	app->animation.radius = 4.0f;
	anim_init(app);
}

