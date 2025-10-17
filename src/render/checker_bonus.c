/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:13:19 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/17 12:16:41 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_rgb	checker_bonus(t_vec3 surface_pos, t_rgb base_color)
{
	int	tile_u;
	int	tile_v;
	int	is_light_tile;

	tile_v = (int)floorf(surface_pos.z);
	tile_u = (int)floorf(surface_pos.x);
	is_light_tile = (tile_u + tile_v) & 1;
	if (is_light_tile)
		return (base_color);
	return ((t_rgb){ base_color.r*0.2f, base_color.g*0.2f, base_color.b*0.2f });
}

