/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:00:00 by yyudi             #+#    #+#             */
/*   Updated: 2025/12/11 15:52:59 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static void	init_mouse_first_frame(t_app *app, double xpos, double ypos)
{
	if (app->mouse_first)
	{
		app->mouse_last_x = xpos;
		app->mouse_last_y = ypos;
		app->mouse_first = 0;
	}
}

static void	update_camera_angles(t_camera *cam, double dx, double dy)
{
	cam->yaw += dx * cam->mouse_sens;
	cam->pitch -= dy * cam->mouse_sens;
	if (cam->pitch > 1.5f)
		cam->pitch = 1.5f;
	if (cam->pitch < -1.5f)
		cam->pitch = -1.5f;
}

static void	compute_direction(t_camera *cam)
{
	t_vec3	dir;

	dir.x = cosf(cam->yaw) * cosf(cam->pitch);
	dir.y = sinf(cam->pitch);
	dir.z = sinf(cam->yaw) * cosf(cam->pitch);
	cam->direction = vnorm(dir);
	camera_build(cam);
}

void	mouse_look_callback(double xpos, double ypos, void *param)
{
	t_app		*app;
	t_camera	*cam;
	double		dx;
	double		dy;

	app = (t_app *)param;
	if (!app)
		return ;
	cam = &app->scene.camera;
	if (!cam)
		return ;
	init_mouse_first_frame(app, xpos, ypos);
	dx = xpos - app->mouse_last_x;
	dy = ypos - app->mouse_last_y;
	app->mouse_last_x = xpos;
	app->mouse_last_y = ypos;
	update_camera_angles(cam, dx, dy);
	compute_direction(cam);
}


