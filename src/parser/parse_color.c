/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:05:47 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 13:05:48 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static int	parse_color_component(const char *color_str, float *color)
{
	int	status;
	int	result;

	status = 0;
	result = ft_atoi_with_checker(color_str, &status);
	if (!status || result < 0 || result > 255)
		return (0);
	*color = result / 255.0f;
	return (1);
}

int	parse_color(const char *s, t_rgb *color)
{
	char	**rgb;

	rgb = ft_split(s, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(rgb), 0);
	if (!parse_color_component(rgb[0], &color->red)
		|| !parse_color_component(rgb[1], &color->green)
		|| !parse_color_component(rgb[2], &color->blue))
	{
		free_split(rgb);
		return (0);
	}
	free_split(rgb);
	return (1);
}
