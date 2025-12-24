/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:59:04 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 13:59:05 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_rgb	rgb_add(t_rgb a, t_rgb b)
{
	t_rgb	out;

	out.red = a.red + b.red;
	out.green = a.green + b.green;
	out.blue = a.blue + b.blue;
	return (out);
}

t_rgb	rgb_mul(t_rgb a, float k)
{
	t_rgb	out;

	out.red = a.red * k;
	out.green = a.green * k;
	out.blue = a.blue * k;
	return (out);
}

t_rgb	rgb_mod(t_rgb a, t_rgb b)
{
	t_rgb	out;

	out.red = a.red * b.red;
	out.green = a.green * b.green;
	out.blue = a.blue * b.blue;
	return (out);
}

t_rgb	rgb_clamp01(t_rgb c)
{
	t_rgb	out;

	out = c;
	if (out.red > 1.0f)
		out.red = 1.0f;
	if (out.green > 1.0f)
		out.green = 1.0f;
	if (out.blue > 1.0f)
		out.blue = 1.0f;
	if (out.red < 0.0f)
		out.red = 0.0f;
	if (out.green < 0.0f)
		out.green = 0.0f;
	if (out.blue < 0.0f)
		out.blue = 0.0f;
	return (out);
}
