#include "ft_minirt.h"

static int	parse_bonus_plane(char **tokens, t_scene *scene)
{
	int		status;
	t_obj	*object;

	status = parse_plane(tokens, scene);
	if (status)
	{
		object = scene->objs;
		while (object && object->next)
			object = object->next;
		if (object && object->type == OBJ_PLANE)
			((t_plane *)object->ptr)->material.checker = 1;
	}
	return (status);
}

int	dispatch(char **tokens, t_scene *scene)
{
	if (str_eq(tokens[0], "A"))
		return (parse_ambient(tokens, scene));
	if (str_eq(tokens[0], "C"))
		return (parse_camera(tokens, scene));
	if (str_eq(tokens[0], "L"))
		return (parse_light(tokens, scene, 0));
	if (str_eq(tokens[0], "sp"))
		return (parse_sphere(tokens, scene));
	if (str_eq(tokens[0], "pl"))
		return (parse_plane(tokens, scene));
	if (str_eq(tokens[0], "cy"))
		return (parse_cylinder(tokens, scene));
	if (str_eq(tokens[0], "l"))
		return (parse_light(tokens, scene, 1));
	if (str_eq(tokens[0], "co"))
		return (parse_cone_bonus(tokens, scene));
	if (str_eq(tokens[0], "pl#"))
		return (parse_bonus_plane(tokens, scene));
	return (0);
}