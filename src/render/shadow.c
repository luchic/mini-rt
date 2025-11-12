/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 11:00:46 by yyudi             #+#    #+#             */
/*   Updated: 2025/11/12 11:10:40 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static int	hit_any(t_scene *sc, t_ray ray_in, float tmax)
{
	t_obj		*node;
	t_ray		rec_tmp;

	node = sc->objs;
	while (node)
	{
		if (node->type == OBJ_SPHERE && hit_sphere((t_sphere *)node->ptr,
				ray_in, &rec_tmp))
			return (1);
		if (node->type == OBJ_PLANE && hit_plane((t_plane *)node->ptr,
				ray_in, tmax, &rec_tmp))
			return (1);
		if (node->type == OBJ_CYLINDER && hit_cylinder((t_cylinder *)node->ptr,
				ray_in, tmax, &rec_tmp))
			return (1);
		if (node->type == OBJ_CONE && hit_cone((t_cone *)node->ptr,
				ray_in, tmax, &rec_tmp))
			return (1);
		node = node->next;
	}
	return (0);
}

int	in_shadow(t_scene *sc, t_vec3 point, t_vec3 light_dir, float light_dist)
{
	t_ray	shadow_ray;

	shadow_ray = ray(vadd(point,
				vmul(light_dir, EPS * 8.0f)),
			light_dir);
	return (hit_any(sc, shadow_ray, light_dist - EPS));
}
