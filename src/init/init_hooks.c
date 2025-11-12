#include "ft_minirt.h"
#include "tetris.h"

static void	on_close(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (app && app->mlx)
		mlx_close_window(app->mlx);
}

// cam_anim_on_key(key, app);
static void	on_key(mlx_key_data_t key, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (!app)
		return ;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(app->mlx);
	if (key.key == MLX_KEY_S && key.action == MLX_PRESS)
		shfx_trigger(app);
}

// cam_anim_update(app, now);
static void	on_loop(void *param)
{
	t_app	*app;
	double	now;

	app = (t_app *)param;
	if (!app)
		return ;
	now = mlx_get_time();
	if (app->tetris_enabled)
		tetris_simple_update(app, now);
	shfx_update(app, now);
	app->last_ts = now;
	if (app->needs_redraw)
		render(app);
}

void	setup_hooks(t_app *app)
{
	mlx_close_hook(app->mlx, on_close, app);
	mlx_key_hook(app->mlx, on_key, app);
	mlx_loop_hook(app->mlx, on_loop, app);
}
