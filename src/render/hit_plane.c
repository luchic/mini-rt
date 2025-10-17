/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:20:52 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/17 14:39:55 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

int	hit_plane(t_plane *pl, t_ray ray_in, float tmax, float *t_hit_out, t_vec3 *normal_out, t_material *mat_out)
{
	float denom = vdot(pl->n, ray_in.d);
	float t_candidate;

	if (fabsf(denom) < EPS) return (0);
	t_candidate = vdot(vsub(pl->p, ray_in.o), pl->n) / denom;
	if (t_candidate < EPS || t_candidate > tmax) return (0);

	*t_hit_out = t_candidate;
	*normal_out = pl->n;
	mat_out->color = pl->m.color;
	mat_out->checker = pl->m.checker;
	mat_out->specular = pl->m.specular;
	mat_out->sp_exp = pl->m.sp_exp;
	mat_out->bump = pl->m.bump;
	return (1);
}
