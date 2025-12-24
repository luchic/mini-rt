/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lamp_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:44:29 by yyudi             #+#    #+#             */
/*   Updated: 2025/12/24 12:44:30 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"
#include <math.h>

static t_rgb	lerp_rgb(t_rgb a, t_rgb b, float t)
{
	t_rgb	o;

	o.red = a.red + (b.red - a.red) * t;
	o.green = a.green + (b.green - a.green) * t;
	o.blue = a.blue + (b.blue - a.blue) * t;
	return (o);
}

static t_rgb	get_sun_color(float k)
{
	const t_rgb	morning = (t_rgb){1.0f, 0.65f, 0.35f};
	const t_rgb	noon = (t_rgb){1.0f, 1.0f, 1.0f};
	const t_rgb	evening = (t_rgb){1.0f, 0.45f, 0.25f};

	if (k < 0.5f)
		return (lerp_rgb(morning, noon, k * 2.0f));
	return (lerp_rgb(noon, evening, (k - 0.5f) * 2.0f));
}

static void	set_sun_pos(t_light *sun, float angle, float radius, float height)
{
	if (!sun)
		return ;
	sun->pos.x = cosf(angle) * radius;
	sun->pos.z = sinf(angle) * radius;
	sun->pos.y = height;
}

static void	set_sun_lighting(t_light *sun, float k)
{
	if (!sun)
		return ;
	if (k < 0.0f)
		k = 0.0f;
	sun->br = 0.2f + k * 1.5f;
	sun->color = get_sun_color(k);
}

void	update_lamp_sun(t_app *app)
{
	t_light	*sun;
	double	time_now;
	float	t;
	float	angle;
	float	height;

	if (!app || !app->lamp_enabled)
		return ;
	sun = app->scene.lights;
	if (!sun)
		return ;
	time_now = mlx_get_time();
	t = (float)(time_now * 0.2f);
	angle = t;
	height = sinf(t) * 10.0f + 15.0f;
	set_sun_pos(sun, angle, 20.0f, height);
	set_sun_lighting(sun, sinf(t));
	app->needs_redraw = 1;
}
