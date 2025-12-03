/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:20:52 by yyudi             #+#    #+#             */
/*   Updated: 2025/11/12 11:17:02 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

int	hit_plane(t_plane *pl, t_ray ray_in, float tmax, t_ray *ray_hit)
{
	t_material	material;
	float		denom;
	float		t_candidate;

	denom = dot_product(pl->normal, ray_in.direction);
	if (fabsf(denom) < EPS)
		return (0);
	t_candidate = dot_product(vsub(pl->position,
				ray_in.origin), pl->normal) / denom;
	if (t_candidate < EPS || t_candidate > tmax)
		return (0);
	material.color = pl->material.color;
	material.checker = pl->material.checker;
	material.specular = pl->material.specular;
	material.sp_exp = pl->material.sp_exp;
	material.bump = pl->material.bump;
	ray_hit->t = t_candidate;
	ray_hit->normal = pl->normal;
	ray_hit->material = material;
	return (1);
}
