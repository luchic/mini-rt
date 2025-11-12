/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:22:37 by yyudi             #+#    #+#             */
/*   Updated: 2025/11/12 11:18:07 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

/* ---- efek permukaan (checker/bump) ------------------------------------- */
static void	apply_surface_effects(t_material *m,
	t_vec3 p, t_vec3 *n, t_rgb *base)
{
	if (m->checker)
		*base = checker_bonus(p, *base);
	if (m->bump)
		*n = bump_bonus(*n, p, m);
}

/* ---- entry point sesuai ft_minirt.h ------------------------------------ */
t_rgb	shade(t_scene *sc, t_ray hit_view, t_vec3 normal, t_material *mat)
{
	t_rgb	amb;
	t_rgb	out;
	t_ray	hv;
	t_vec3	n;

	hv = hit_view;
	hv.material = *mat;
	n = normal;
	apply_surface_effects(&hv.material, hv.origin, &n, &hv.material.color);
	amb = rgb_mul(sc->amb_color, sc->amb);
	out = rgb_add(amb, accum_lights(sc, hv, n));
	return (rgb_clamp01(out));
}
