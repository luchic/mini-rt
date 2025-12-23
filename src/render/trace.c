/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:17:24 by yyudi             #+#    #+#             */
/*   Updated: 2025/12/22 16:00:03 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_vec3	view_dir;

	if (!hit_all(sc, r, &hit_r))
		return (0);
	hit_p = vadd(r.origin, vmul(r.direction, hit_r.t));
	hit_r.origin = hit_p;
	view_dir = vmul(r.direction, -1.0f);
	*col_out = shade(sc, hit_r, view_dir);
	return (1);
}
