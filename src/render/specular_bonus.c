/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:23:09 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/18 11:15:59 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_rgb	specular_bonus(t_vec3 n, t_vec3 l, t_vec3 v, t_material *m)
{
	t_vec3	half_vec;
	float	n_dot_h;
	float	spec_intensity;
	t_rgb	spec_color;

	half_vec = vnorm(vadd(l, v));
	n_dot_h = vdot(n, half_vec);
	if (n_dot_h < 0)
		n_dot_h = 0;
	if (m->sp_exp <= 1)
		spec_intensity = powf(n_dot_h, 16.0f);
	else
		spec_intensity = powf(n_dot_h, m->sp_exp);
	if (m->specular <= 0)
		spec_intensity = spec_intensity * 0.2f;
	else
		spec_intensity = spec_intensity * m->specular;
	spec_color.r = spec_intensity;
	spec_color.g = spec_intensity;
	spec_color.b = spec_intensity;
	return (spec_color);
}