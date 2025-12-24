/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:05:25 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 13:05:26 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static int	parse_sphere_fields(char **tokens, t_sphere *sphere)
{
	t_rgb		color;
	t_vec3		center;
	float		diameter;

	if (!parse_v3(tokens[1], &center))
		return (0);
	if (!parse_float(tokens[2], &diameter, 0.0f, 1e6))
		return (0);
	if (!parse_color(tokens[3], &color))
		return (0);
	sphere->center = center;
	sphere->radius = diameter * 0.5f;
	sphere->material.color = color;
	return (1);
}

int	parse_sphere(char **tokens, t_scene *scene)
{
	t_sphere	*sphere;

	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (0);
	sphere = (t_sphere *)emalloc(sizeof(t_sphere));
	if (!parse_sphere_fields(tokens, sphere))
		return (ft_free(sphere), 0);
	sphere->material.checker = 0;
	sphere->material.specular = 0.2f;
	sphere->material.sp_exp = 32;
	sphere->material.bump = (tokens[4] && ft_strcmp(tokens[4], "bm") == 0);
	sphere->material.has_normal_map = 0;
	sphere->material.normal_tex = NULL;
	if (tokens[4] && ft_strncmp(tokens[4], "nm:", 3) == 0)
	{
		sphere->material.normal_tex = mlx_load_png(tokens[4] + 3);
		sphere->material.has_normal_map = (sphere->material.normal_tex != NULL);
	}
	scene_add_obj(scene, new_obj(OBJ_SPHERE, sphere));
	return (1);
}
