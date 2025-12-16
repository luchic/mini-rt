#include "ft_minirt.h"

int	parse_sphere(char **tokens, t_scene *scene)
{
	t_sphere	*sphere;
	t_rgb		color;
	t_vec3		center;
	float		diameter;

	/* allow optional 5th token (bm or nm:path) */
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (0);
	if (!parse_v3(tokens[1], &center))
		return (0);
	if (!parse_float(tokens[2], &diameter, 0.0f, 1e6))
		return (0);
	if (!parse_color(tokens[3], &color))
		return (0);
	sphere = (t_sphere *)emalloc(sizeof(t_sphere));
	sphere->center = center;
	sphere->radius = diameter * 0.5f;
	sphere->material.color = color;
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

int	parse_plane(char **tokens, t_scene *scene)
{
	t_plane	*pl;
	t_rgb		color;
	t_vec3		pos;
	t_vec3		normal;

	/* allow optional 5th token (bm or nm:path) */
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (0);
	if (!parse_v3(tokens[1], &pos))
		return (0);
	if (!parse_norm_v3(tokens[2], &normal))
		return (0);
	if (!parse_color(tokens[3], &color))
		return (0);
	pl = (t_plane *)emalloc(sizeof(t_plane));
	pl->position = pos;
	pl->normal = normal;
	pl->material.color = color;
	pl->material.checker = 0;
	pl->material.specular = 0.2f;
	pl->material.sp_exp = 32;
	pl->material.bump = (tokens[4] && ft_strcmp(tokens[4], "bm") == 0);
	pl->material.has_normal_map = 0;
	pl->material.normal_tex = NULL;
	if (tokens[4] && ft_strncmp(tokens[4], "nm:", 3) == 0)
	{
		pl->material.normal_tex = mlx_load_png(tokens[4] + 3);
		pl->material.has_normal_map = (pl->material.normal_tex != NULL);
	}
	scene_add_obj(scene, new_obj(OBJ_PLANE, pl));
	return (1);
}

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

int	parse_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	*cylinder;
	t_rgb		color;
	t_vec3		center;
	t_vec3		axis;

	/* allow optional 7th token (bm or nm:path) */
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
		return (0);
	cylinder = (t_cylinder *)emalloc(sizeof(t_cylinder));
	if (!parse_cylinder_metric(cylinder, tokens))
		return (ft_free(cylinder), 0);
	if (!parse_v3(tokens[1], &center))
		return (ft_free(cylinder), 0);
	if (!parse_norm_v3(tokens[2], &axis))
		return (ft_free(cylinder), 0);
	if (!parse_color(tokens[5], &color))
		return (ft_free(cylinder), 0);
	cylinder->center = center;
	cylinder->axis = axis;
	cylinder->material.color = color;
	cylinder->material.checker = 0;
	cylinder->material.specular = 0.2f;
	cylinder->material.sp_exp = 32;
	cylinder->material.bump = (tokens[6] && ft_strcmp(tokens[6], "bm") == 0);
	cylinder->material.has_normal_map = 0;
	cylinder->material.normal_tex = NULL;
	if (tokens[6] && ft_strncmp(tokens[6], "nm:", 3) == 0)
	{
		cylinder->material.normal_tex = mlx_load_png(tokens[6] + 3);
		cylinder->material.has_normal_map = (cylinder->material.normal_tex != NULL);
	}
	return (scene_add_obj(scene, new_obj(OBJ_CYLINDER, cylinder)), 1);
}
