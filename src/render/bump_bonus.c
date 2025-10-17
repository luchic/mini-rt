/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:13:13 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/17 16:15:50 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static float	snoise(float x, float y)
{
	return (
		sinf(x * 2.3f) * cosf(y * 1.7f) * 0.5f + 0.5f
	);
}

t_vec3	bump_bonus(t_vec3 surface_normal,
			t_vec3 surface_pos, t_material *mat_out)
{
	float	amplitude;
	t_vec3	tangent_u;
	t_vec3	tangent_v;
	float	noise;
	t_vec3	bump_vec;

	amplitude = 0.25f;
	tangent_u = vnorm(vcross(surface_normal, v3(0.0f, 1.0f, 0.0f)));
	tangent_v = vcross(surface_normal, tangent_u);
	noise = snoise(surface_pos.x * 0.5f, surface_pos.z * 0.5f);
	bump_vec = vadd(
			vmul(tangent_u, (noise - 0.5f) * amplitude),
			vmul(tangent_v, (0.5f - noise) * amplitude));
	(void)mat_out;
	return (vnorm(vadd(surface_normal, bump_vec)));
}
