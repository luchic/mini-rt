/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:19:32 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 13:07:30 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static int	resize_window(t_app *app, int32_t width, int32_t height)
{
	if (app->img.img)
	{
		mlx_delete_image(app->mlx, app->img.img);
		app->img.img = NULL;
	}
	app->img.img = mlx_new_image(app->mlx, width, height);
	if (!app->img.img)
	{
		ft_printf("ERROR: mlx_new_image failed\n");
		return (0);
	}
	if (mlx_image_to_window(app->mlx, app->img.img, 0, 0) < 0)
	{
		ft_printf("ERROR: mlx_image_to_window failed\n");
		mlx_delete_image(app->mlx, app->img.img);
		app->img.img = NULL;
		return (0);
	}
	return (1);
}

void	on_resize(int32_t width, int32_t height, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	ft_printf("RESIZE: %d x %d\n", width, height);
	if (!app || !app->mlx || width < 100 || height < 100)
		return ;
	if (!resize_window(app, width, height))
		return ;
	app->width = width;
	app->height = height;
	app->img.width = width;
	app->img.height = height;
	set_render_context(app);
	app->needs_redraw = 1;
	ft_printf("Resize OK\n");
}
