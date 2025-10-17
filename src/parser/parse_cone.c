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

int	parse_cone_bonus(char **tokens, t_scene *scene)
{
	t_cone	*cone;
	t_rgb	color;
	t_vec3	center;
	t_vec3	axis;

	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5]
		|| tokens[6])
		return (0);
	cone = (t_cone *)emalloc(sizeof(t_cone));
	if (!parse_v3(tokens[1], &center))
		return (ft_free(cone), 0);
	if (!parse_norm_v3(tokens[2], &axis))
		return (ft_free(cone), 0);
	if (!parse_cone_metric(cone, tokens))
		return (ft_free(cone), 0);
	if (!parse_color(tokens[5], &color))
		return (ft_free(cone), 0);
	cone->center = center;
	cone->axis = axis;
	cone->material.color = color;
	cone->material.checker = 0;
	cone->material.specular = 0.25f;
	cone->material.sp_exp = 48;
	cone->material.bump = 0;
	return (scene_add_obj(scene, new_obj(OBJ_CONE, cone)), 1);
}
