/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:20:52 by yyudi             #+#    #+#             */
/*   Updated: 2025/12/22 18:34:16 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static void	set_plane_local_p(t_ray ray_in,
	float t_candidate, t_plane *pl, t_ray *ray_hit)
{
	t_vec3	p;
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	local;

	p = vadd(ray_in.origin, vmul(ray_in.direction, t_candidate));
	tangent = vnorm(vcross_product(vec3(0.0f, 1.0f, 0.0f), pl->normal));
	if (dot_product(tangent, tangent) < EPS)
		tangent = vnorm(vcross_product(vec3(1.0f, 0.0f, 0.0f), pl->normal));
	bitangent = vcross_product(pl->normal, tangent);
	local = vsub(p, pl->position);
	ray_hit->local_p = vec3(dot_product(local, tangent), 0.0f,
			dot_product(local, bitangent));
}

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
	material.has_normal_map = pl->material.has_normal_map;
	material.normal_tex = pl->material.normal_tex;
	ray_hit->t = t_candidate;
	ray_hit->normal = pl->normal;
	ray_hit->type = OBJ_PLANE;
	set_plane_local_p(ray_in, t_candidate, pl, ray_hit);
	ray_hit->material = material;
	return (1);
}
