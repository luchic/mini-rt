#include "ft_minirt.h"

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
	if (key.key == MLX_KEY_K && key.action == MLX_PRESS)
		shfx_trigger(app);
	if (key.key == MLX_KEY_L && key.action == MLX_PRESS)
		lamp_toggle(app);
	if (key.key == MLX_KEY_R && key.action == MLX_PRESS)
	{
		water_trigger_ripple(app, 0.5f, 0.5f);
		app->needs_redraw = 1;
	}
	// cam_anim_on_key(key, app);
}

static void	on_loop(void *param)
{
	t_app	*app;
	double	now;

	app = (t_app *)param;
	if (!app || !app->mlx)
		return ;
	now = mlx_get_time();

	shfx_update(app, now);
	cam_anim_update(app, now);
	update_lamp_sun(app); 

	water_update(app, now);
	if (app->needs_redraw)
		render(app);
	/* `cam_anim_update` (and other updaters) manage their own timing
	   — do not overwrite `app->last_ts` unconditionally here, it
	   prevents the animator from seeing the elapsed time correctly. */
}

void	setup_hooks(t_app *app)
{
    mlx_close_hook(app->mlx, on_close, app);
    mlx_key_hook(app->mlx, on_key, app);

    /* register mouse look + capture the cursor so mouse deltas work */
    mlx_cursor_hook(app->mlx, mouse_look_callback, app);
    mlx_set_cursor_mode(app->mlx, MLX_MOUSE_DISABLED);

    mlx_loop_hook(app->mlx, on_loop, app);
}
