/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spotlight.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:05:22 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 13:05:23 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static int	set_spotlight(t_scene *scene, t_light *light)
{
	t_light	*it;

	if (!scene->lights)
		scene->lights = light;
	else
	{
		it = scene->lights;
		while (it->next)
			it = it->next;
		it->next = light;
	}
	return (1);
}

static int	parse_spotlight_fields(char **tokens, t_light *light)
{
	t_vec3	pos;
	t_vec3	dir;
	float	brightness;
	t_rgb	color;
	float	cutoff_deg;

	if (!parse_v3(tokens[1], &pos))
		return (0);
	if (!parse_norm_v3(tokens[2], &dir))
		return (0);
	if (!parse_float(tokens[3], &brightness, 0.0f, 1.0f))
		return (0);
	if (!parse_color(tokens[4], &color))
		return (0);
	if (!parse_float(tokens[5], &cutoff_deg, 1.0f, 90.0f))
		return (0);
	light->pos = pos;
	light->dir = dir;
	light->br = brightness;
	light->color = color;
	light->cutoff_cos = cosf(cutoff_deg * PI_F / 180.0f);
	return (1);
}

int	parse_spotlight(char **tokens, t_scene *scene)
{
	t_light	*light;

	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5]
		|| tokens[6])
		return (0);
	light = (t_light *)emalloc(sizeof(t_light));
	if (!parse_spotlight_fields(tokens, light))
		return (ft_free(light), 0);
	light->type = LIGHT_SPOT;
	light->next = NULL;
	return (set_spotlight(scene, light));
}
