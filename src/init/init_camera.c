#include "ft_minirt.h"

// static t_vec3	choose_up(t_vec3 dir)
// {
// 	t_vec3	up;

// 	up = vec3(0, 1, 0);
// 	if (fabsf(dir.y) > 0.99f)
// 		up = vec3(0, 0, 1);
// 	return (up);
// }

// g_mode = LIGHT_NORMAL;
// void	init_camera_animation(t_app *app)
// {
// 	if (!app)
// 		return ;
// 	app->animation.enabled = 1;
// 	app->animation.speed = 0.6f;
// 	app->animation.radius = 4.0f;
// 	app->last_ts = mlx_get_time();
// 	//anim_init(app);
// }

void	init_camera_animation(t_app *app)
{
    if (!app)
        return ;
    app->animation.enabled = 1;
    app->animation.speed = 0.6f;
    app->animation.radius = 4.0f;
    app->last_ts = mlx_get_time();

    /* camera movement defaults used by cam mouse & anim */
    app->scene.camera.move_speed = 4.0f;
    app->scene.camera.mouse_sens = 0.0025f;
    /* init yaw/pitch from direction so mouse look is continuous */
    app->scene.camera.yaw = atan2f(app->scene.camera.direction.z, app->scene.camera.direction.x);
    app->scene.camera.pitch = asinf(app->scene.camera.direction.y);
    //anim_init(app);
}