/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:22:37 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/17 12:22:38 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_rgb	add_rgb(t_rgb a, t_rgb b)
{
	t_rgb out;
	out.r = a.r + b.r;
	out.g = a.g + b.g;
	out.b = a.b + b.b;
	return (out);
}
static t_rgb	mul_rgb(t_rgb a, float k)
{
	t_rgb out;
	out.r = a.r * k;
	out.g = a.g * k;
	out.b = a.b * k;
	return (out);
}
static t_rgb	modulate(t_rgb a, t_rgb b)
{
	t_rgb out;
	out.r = a.r * b.r;
	out.g = a.g * b.g;
	out.b = a.b * b.b;
	return (out);
}

t_rgb	shade(t_scene *sc, t_v3 hit_pos, t_v3 surface_normal, t_mat *mat_in, t_v3 view_dir)
{
	(void)view_dir;
	t_light *light = sc->lights;
	t_rgb shaded = mul_rgb(sc->amb_color, sc->amb);
	t_rgb base_color = mat_in->color;

#ifdef BONUS
	if (mat_in->checker) base_color = checker_bonus(hit_pos, base_color);
	if (mat_in->bump) surface_normal = bump_bonus(surface_normal, hit_pos, mat_in);
#endif

	while (light)
	{
		t_v3 to_light = vsub(light->pos, hit_pos);
		float light_dist = vlen(to_light);
		to_light = vdivv(to_light, light_dist);
		if (!in_shadow(sc, hit_pos, to_light, light_dist))
		{
			float ndotl = vdot(surface_normal, to_light);
			if (ndotl > 0.0f)
			{
				t_rgb diffuse = mul_rgb(modulate(base_color, light->color), ndotl * light->br);
				shaded = add_rgb(shaded, diffuse);
#ifdef BONUS
				{
					t_rgb spec = specular_bonus(surface_normal, to_light, view_dir, mat_in);
					shaded = add_rgb(shaded, mul_rgb(modulate(light->color, spec), light->br));
				}
#endif
			}
		}
		light = light->next;
	}
	if (shaded.r > 1) shaded.r = 1;
	if (shaded.g > 1) shaded.g = 1;
	if (shaded.b > 1) shaded.b = 1;
	return (shaded);
}
