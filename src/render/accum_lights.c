/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accum_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 14:01:25 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 14:01:26 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

/* ---- loop semua lampu --------------------------------------------------- */
t_rgb	accum_lights(t_scene *sc, t_ray hv, t_vec3 n)
{
	t_light	*it;
	t_rgb	sum;

	sum.red = 0.0f;
	sum.green = 0.0f;
	sum.blue = 0.0f;
	it = sc->lights;
	while (it)
	{
		sum = rgb_add(sum, accum_light_once(sc, it, hv, n));
		it = it->next;
	}
	return (sum);
}
