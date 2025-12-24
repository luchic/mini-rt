/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:05:52 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 13:05:53 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

int	parse_ambient_light(char **tokens, t_scene *scene)
{
	float	ratio;
	t_rgb	color;

	if (scene->has_a)
		return (0);
	if (!tokens[1] || !tokens[2] || tokens[3])
		return (0);
	if (!parse_float(tokens[1], &ratio, 0.0f, 1.0f))
		return (0);
	if (!parse_color(tokens[2], &color))
		return (0);
	scene->amb = ratio;
	scene->amb_color = color;
	scene->has_a = 1;
	return (1);
}
