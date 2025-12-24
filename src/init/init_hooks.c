/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:07:23 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 13:07:24 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static void	on_close(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (app && app->mlx)
		mlx_close_window(app->mlx);
}

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

void	setup_hooks(t_app *app)
{
	mlx_close_hook(app->mlx, on_close, app);
	mlx_key_hook(app->mlx, on_key, app);
	mlx_cursor_hook(app->mlx, mouse_look_callback, app);
	mlx_resize_hook(app->mlx, on_resize, app);
	mlx_mouse_hook(app->mlx, on_mouse_button, app);
	mlx_loop_hook(app->mlx, on_loop, app);
}
