/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:07:15 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 13:07:19 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	init_camera_animation(t_app *app)
{
	if (!app)
		return ;
	app->animation.enabled = 1;
	app->animation.speed = 0.6f;
	app->animation.radius = 4.0f;
	app->last_ts = mlx_get_time();
	app->scene.camera.move_speed = 4.0f;
	app->scene.camera.mouse_sens = 0.0025f;
	app->scene.camera.yaw = atan2f(app->scene.camera.direction.z,
			app->scene.camera.direction.x);
	app->scene.camera.pitch = asinf(app->scene.camera.direction.y);
}
