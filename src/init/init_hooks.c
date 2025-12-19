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
	if (key.key == MLX_KEY_M && key.action == MLX_PRESS)
	{
		app->mouse_look_enabled = !app->mouse_look_enabled;
		app->mouse_first = 1;
		if (app->mouse_look_enabled)
			mlx_set_cursor_mode(app->mlx, MLX_MOUSE_DISABLED);
		else
			mlx_set_cursor_mode(app->mlx, MLX_MOUSE_NORMAL);
	}
}

static void	on_mouse_button(mouse_key_t button, action_t action,
	modifier_key_t mods, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (!app)
		return ;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_MIDDLE && action == MLX_PRESS)
	{
		app->mouse_look_enabled = !app->mouse_look_enabled;
		app->mouse_first = 1;
		if (app->mouse_look_enabled)
			mlx_set_cursor_mode(app->mlx, MLX_MOUSE_DISABLED);
		else
			mlx_set_cursor_mode(app->mlx, MLX_MOUSE_NORMAL);
	}
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
	if (app->needs_redraw)
		render(app);
}

static void	on_resize(int32_t width, int32_t height, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (!app || !app->mlx || width <= 0 || height <= 0)
		return ;
	if (app->img.img)
		mlx_delete_image(app->mlx, app->img.img);
	app->width = width;
	app->height = height;
	app->img.img = mlx_new_image(app->mlx, width, height);
	if (!app->img.img)
		return ;
	app->img.width = width;
	app->img.height = height;
	if (mlx_image_to_window(app->mlx, app->img.img, 0, 0) < 0)
	{
		mlx_delete_image(app->mlx, app->img.img);
		app->img.img = NULL;
		return ;
	}
	set_render_context(app);
	app->needs_redraw = 1;
}

void	setup_hooks(t_app *app)
{
	mlx_close_hook(app->mlx, on_close, app);
	mlx_key_hook(app->mlx, on_key, app);
	mlx_cursor_hook(app->mlx, mouse_look_callback, app);
	mlx_resize_hook(app->mlx, on_resize, app);
	mlx_mouse_hook(app->mlx, on_mouse_button, app);
	mlx_loop_hook(app->mlx, on_loop, app);
}
