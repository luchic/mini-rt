/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:05:49 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 13:05:50 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

int	parse_camera(char **tokens, t_scene *scene)
{
	float	fov;
	t_vec3	pos;
	t_vec3	direction;

	if (scene->has_c)
		return (0);
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (0);
	if (!parse_v3(tokens[1], &pos))
		return (0);
	if (!parse_norm_v3(tokens[2], &direction))
		return (0);
	if (!parse_float(tokens[3], &fov, 0.0f, 180.0f))
		return (0);
	scene->camera.pos = pos;
	scene->camera.direction = direction;
	scene->camera.fov_deg = fov;
	scene->has_c = 1;
	return (1);
}
