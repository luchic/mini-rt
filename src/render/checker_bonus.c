/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:13:19 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/27 13:58:58 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_rgb	checker_bonus(t_vec3 surface_pos, t_rgb base_color)
{
	int		tile_u;
	int		tile_v;
	int		is_light_tile;
	t_rgb	dark;

	tile_v = (int)floorf(surface_pos.z);
	tile_u = (int)floorf(surface_pos.x);
	is_light_tile = (tile_u + tile_v) & 1;
	if (is_light_tile)
		return (base_color);
	dark = (t_rgb){
		base_color.red * 0.2f,
		base_color.green * 0.2f,
		base_color.blue * 0.2f
	};
	return (dark);
}

