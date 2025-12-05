/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:17:24 by yyudi             #+#    #+#             */
/*   Updated: 2025/11/12 11:10:51 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_minirt.h"

/* ============================ tracing ============================ */

static int	try_hit_node(t_obj *node, t_ray r, float tmax, t_ray *hit_out)
{
	int	status;

	status = 0;
	if (node->type == OBJ_SPHERE)
		status = hit_sphere((t_sphere *)node->ptr, r, hit_out);
	else if (node->type == OBJ_PLANE)
		status = hit_plane((t_plane *)node->ptr, r, tmax, hit_out);
	else if (node->type == OBJ_CYLINDER)
		status = hit_cylinder((t_cylinder *)node->ptr, r, tmax, hit_out);
	else if (node->type == OBJ_CONE)
		status = hit_cone((t_cone *)node->ptr, r, tmax, hit_out);
	return (status);
}

static int	hit_all(t_scene *sc, t_ray r, t_ray *hit_out)
{
	t_obj	*it;
	float	best_t;
	t_ray	cur;
	int		any;

	it = sc->objs;
	best_t = TMAX;
	any = 0;
	while (it)
	{
		if (try_hit_node(it, r, best_t, &cur))
		{
			any = 1;
			best_t = cur.t;
			*hit_out = cur;
		}
		it = it->next;
	}
	return (any);
}

int	trace_ray(t_scene *sc, t_ray r, t_rgb *col_out)
{
	t_ray	hit_r;
	t_vec3	hit_p;
	t_ray	view_r;

	if (!hit_all(sc, r, &hit_r))
		return (0);
	hit_p = vadd(r.origin, vmul(r.direction, hit_r.t));
	view_r = ray(hit_p, vmul(r.direction, -1.0f));
	*col_out = shade(sc, view_r, hit_r.normal, &hit_r.material);
	return (1);
}
