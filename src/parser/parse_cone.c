#include "ft_minirt.h"

static int	parse_cone_metric(t_cone *cone, char **tok)
{
	float	angle;
	float	height;

	if (!parse_float(tok[3], &angle, 0.1f, 89.9f))
		return (0);
	if (!parse_float(tok[4], &height, 0.0f, 1e6))
		return (0);
	cone->angle = angle * PI_F / 180.0f;
	cone->height = height;
	return (1);
}

static int	parse_fields(t_cone *cone, char **tokens)
{
	t_rgb	color;
	t_vec3	center;
	t_vec3	axis;

	if (!parse_v3(tokens[1], &center))
		return (0);
	if (!parse_norm_v3(tokens[2], &axis))
		return (0);
	if (!parse_color(tokens[5], &color))
		return (0);
	cone->center = center;
	cone->axis = axis;
	cone->material.color = color;
	return (1);
}

int	parse_cone_bonus(char **tokens, t_scene *scene)
{
	t_cone	*cone;

	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
		return (0);
	cone = (t_cone *)emalloc(sizeof(t_cone));
	if (!parse_fields(cone, tokens))
		return (ft_free(cone), 0);
	if (!parse_cone_metric(cone, tokens))
		return (ft_free(cone), 0);
	cone->material.checker = 0;
	cone->material.specular = 0.25f;
	cone->material.sp_exp = 48;
	cone->material.bump = (tokens[6] && ft_strcmp(tokens[6], "bm") == 0);
	cone->material.has_normal_map = 0;
	cone->material.normal_tex = NULL;
	if (tokens[6] && ft_strncmp(tokens[6], "nm:", 3) == 0)
	{
		cone->material.normal_tex = mlx_load_png(tokens[6] + 3);
		cone->material.has_normal_map = (cone->material.normal_tex != NULL);
	}
	return (scene_add_obj(scene, new_obj(OBJ_CONE, cone)), 1);
}
