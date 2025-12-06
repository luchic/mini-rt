/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:00:00 by yyudi             #+#    #+#             */
/*   Updated: 2025/12/06 12:08:01 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static double	g_last_x = 0.0;
static double	g_last_y = 0.0;
static int		g_first = 1;

static void	init_mouse_first_frame(double xpos, double ypos)
{
	if (g_first)
	{
		g_last_x = xpos;
		g_last_y = ypos;
		g_first = 0;
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
	init_mouse_first_frame(xpos, ypos);
	dx = xpos - g_last_x;
	dy = ypos - g_last_y;
	g_last_x = xpos;
	g_last_y = ypos;
	update_camera_angles(cam, dx, dy);
	compute_direction(cam);
}

