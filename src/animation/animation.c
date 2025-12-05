#include "ft_minirt.h"

/* ===========================================================
**  Utility movement vector math
** ===========================================================
*/

static t_vec3 vec_scale(t_vec3 v, float k)
{
	return vec3(v.x * k, v.y * k, v.z * k);
}

/* ===========================================================
**  Free camera movement (WASD + vertical movement)
** ===========================================================
*/

static void camera_free_move(t_app *app, double dt)
{
	t_camera *cam = &app->scene.camera;
	float speed = 3.0f * dt;

	t_vec3 forward = vnorm(cam->direction);
	t_vec3 right = vnorm(vcross_product(forward, vec3(0, 1, 0)));

	if (mlx_is_key_down(app->mlx, MLX_KEY_W))
		cam->pos = vadd(cam->pos, vec_scale(forward, speed));
	if (mlx_is_key_down(app->mlx, MLX_KEY_S))
		cam->pos = vsub(cam->pos, vec_scale(forward, speed));
	if (mlx_is_key_down(app->mlx, MLX_KEY_A))
		cam->pos = vsub(cam->pos, vec_scale(right, speed));
	if (mlx_is_key_down(app->mlx, MLX_KEY_D))
		cam->pos = vadd(cam->pos, vec_scale(right, speed));

	if (mlx_is_key_down(app->mlx, MLX_KEY_SPACE))
		cam->pos.y += speed;
	if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT_CONTROL))
		cam->pos.y -= speed;

	camera_build(cam);
}

/* ===========================================================
**  Optional camera rotation (LEFT & RIGHT ARROWS)
**  Bisa kamu aktifkan kapan saja
** ===========================================================
*/

static t_vec3	rot_y(t_vec3 v, float ang)
{
	float	c;
	float	s;

	c = cosf(ang);
	s = sinf(ang);
	return (vec3(
			c * v.x + s * v.z,
			v.y,
			-s * v.x + c * v.z
		));
}

static void	camera_rotate(t_app *app, double dt)
{
	t_camera	*cam;
	float		rs;

	cam = &app->scene.camera;
	rs = 1.5f * dt;
	if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT))
		cam->direction = vnorm(rot_y(cam->direction, -rs));
	if (mlx_is_key_down(app->mlx, MLX_KEY_RIGHT))
		cam->direction = vnorm(rot_y(cam->direction, rs));

	camera_build(cam);
}

/* ===========================================================
**  Init animation timestamp
** ===========================================================
*/

void	anim_init(t_app *app)
{
	if (!app)
		return ;
	app->last_ts = mlx_get_time();
}

/* ===========================================================
**  Animation update per frame
** ===========================================================
*/

void	cam_anim_update(t_app *app, double now)
{
	double	dt;

	if (!app)
		return ;
	if (!app->animation.enabled)
		return ;

	dt = now - app->last_ts;
	if (dt < (1.0 / 60.0))
		return ;

	app->last_ts = now;
	camera_free_move(app, dt);
	camera_rotate(app, dt);
	app->needs_redraw = 1;
}
