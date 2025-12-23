/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:13:19 by yyudi             #+#    #+#             */
/*   Updated: 2025/12/22 18:38:50 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"
#include <math.h>

static float	tile_noise(int u, int v)
{
	int	h;

	h = (u * 374761393 + v * 668265263) ^ (u * 2166136261);
	h = (h ^ (h >> 13)) * 1274126177;
	return ((h & 0xFFFF) / 65536.0f);
}

static t_rgb	tile_variation(t_rgb base, int u, int v)
{
	float	noise;
	float	variation;
	t_rgb	result;

	noise = tile_noise(u, v);
	variation = 0.85f + noise * 0.3f;
	result.red = base.red * variation;
	result.green = base.green * variation;
	result.blue = base.blue * variation;
	return (result);
}

static t_rgb	grout_color(t_vec3 pos, t_rgb tile_col)
{
	float	fx;
	float	fz;
	float	grout_width;
	t_rgb	grout;

	fx = pos.x - floorf(pos.x);
	fz = pos.z - floorf(pos.z);
	grout_width = 0.05f;
	if (fx < grout_width || fx > (1.0f - grout_width)
		|| fz < grout_width || fz > (1.0f - grout_width))
	{
		grout.red = tile_col.red * 0.5f;
		grout.green = tile_col.green * 0.5f;
		grout.blue = tile_col.blue * 0.5f;
		return (grout);
	}
	return (tile_col);
}

t_rgb	checker_bonus(t_vec3 surface_pos, t_rgb base_color)
{
	int		tile_u;
	int		tile_v;
	int		is_light_tile;
	t_rgb	light_tile;
	t_rgb	dark_tile;

	tile_v = (int)floorf(surface_pos.z);
	tile_u = (int)floorf(surface_pos.x);
	is_light_tile = (tile_u + tile_v) & 1;
	light_tile = tile_variation(base_color, tile_u, tile_v);
	dark_tile.red = base_color.red * 0.3f;
	dark_tile.green = base_color.green * 0.3f;
	dark_tile.blue = base_color.blue * 0.3f;
	dark_tile = tile_variation(dark_tile, tile_u, tile_v);
	if (is_light_tile)
		return (grout_color(surface_pos, light_tile));
	else
		return (grout_color(surface_pos, dark_tile));
}
