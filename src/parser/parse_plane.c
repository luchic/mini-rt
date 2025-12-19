#include "ft_minirt.h"

static int	parse_plane_fields(char **tokens, t_plane *plane)
{
	t_rgb		color;
	t_vec3		pos;
	t_vec3		normal;

	if (!parse_v3(tokens[1], &pos))
		return (0);
	if (!parse_norm_v3(tokens[2], &normal))
		return (0);
	if (!parse_color(tokens[3], &color))
		return (0);
	plane->position = pos;
	plane->normal = normal;
	plane->material.color = color;
	return (1);
}

int	parse_plane(char **tokens, t_scene *scene)
{
	t_plane	*pl;

	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (0);
	pl = (t_plane *)emalloc(sizeof(t_plane));
	if (!parse_plane_fields(tokens, pl))
		return (ft_free(pl), 0);
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
