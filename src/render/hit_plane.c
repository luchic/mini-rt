/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:20:52 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/27 14:34:17 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

int	hit_plane(t_plane *pl, t_ray ray_in, float tmax, float *t_hit_out, t_vec3 *normal_out, t_material *mat_out)
{
	float denom = dot_product(pl->normal, ray_in.direction);
	float t_candidate;

	if (fabsf(denom) < EPS) return (0);
	t_candidate = dot_product(vsub(pl->position, ray_in.origin), pl->normal) / denom;
	if (t_candidate < EPS || t_candidate > tmax) return (0);

	*t_hit_out = t_candidate;
	*normal_out = pl->normal;
	mat_out->color = pl->material.color;
	mat_out->checker = pl->material.checker;
	mat_out->specular = pl->material.specular;
	mat_out->sp_exp = pl->material.sp_exp;
	mat_out->bump = pl->material.bump;
	return (1);
}
