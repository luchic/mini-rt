#include "ft_minirt.h"

static int	parse_cylinder_metric(t_cylinder *cylinder, char **tokens)
{
	float	diameter;
	float	height;

	if (!parse_float(tokens[3], &diameter, 0.0f, 1e6))
		return (0);
	if (!parse_float(tokens[4], &height, 0.0f, 1e6))
		return (0);
	cylinder->radius = diameter * 0.5f;
	cylinder->height = height;
	return (1);
}

static int	parse_cylinder_fileds(char **tokens, t_cylinder *cylinder)
{
	t_rgb		color;
	t_vec3		center;
	t_vec3		axis;

	if (!parse_cylinder_metric(cylinder, tokens))
		return (0);
	if (!parse_v3(tokens[1], &center))
		return (0);
	if (!parse_norm_v3(tokens[2], &axis))
		return (0);
	if (!parse_color(tokens[5], &color))
		return (0);
	cylinder->center = center;
	cylinder->axis = axis;
	cylinder->material.color = color;
	return (1);
}

/* allow optional 7th token (bm or nm:path) */
int	parse_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	*cylinder;

	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
		return (0);
	cylinder = (t_cylinder *)emalloc(sizeof(t_cylinder));
	if (!parse_cylinder_fileds(tokens, cylinder))
		return (ft_free(cylinder), 0);
	cylinder->material.checker = 0;
	cylinder->material.specular = 0.2f;
	cylinder->material.sp_exp = 32;
	cylinder->material.bump = (tokens[6] && ft_strcmp(tokens[6], "bm") == 0);
	cylinder->material.has_normal_map = 0;
	cylinder->material.normal_tex = NULL;
	if (tokens[6] && ft_strncmp(tokens[6], "nm:", 3) == 0)
	{
		cylinder->material.normal_tex = mlx_load_png(tokens[6] + 3);
		cylinder->material.has_normal_map = (cylinder->material.normal_tex
				!= NULL);
	}
	return (scene_add_obj(scene, new_obj(OBJ_CYLINDER, cylinder)), 1);
}
