/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_context.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 14:01:32 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 14:01:32 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"
#include <math.h>

void	set_render_context(t_app *app)
{
	app->render_ctx.aspect = (float)app->width / (float)app->height;
	app->render_ctx.fov_rad = app->scene.camera.fov_deg * PI_F / 180.0f;
	app->render_ctx.scale = tanf(app->render_ctx.fov_rad * 0.5f);
}
