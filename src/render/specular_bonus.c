/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:23:09 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/17 14:18:50 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_rgb	specular_bonus(t_vec3 n, t_vec3 l, t_vec3 v, t_material *m)
{
	t_vec3 half_vec = vnorm(vadd(l, v));
	float n_dot_h = vdot(n, half_vec);
	float spec_intensity;
	t_rgb spec_color;

	if (n_dot_h < 0) n_dot_h = 0;
	spec_intensity = powf(n_dot_h, (m->sp_exp <= 1 ? 16.0f : m->sp_exp))
	               * (m->specular <= 0 ? 0.2f : m->specular);
	spec_color.r = spec_intensity;
	spec_color.g = spec_intensity;
	spec_color.b = spec_intensity;
	return (spec_color);
}

