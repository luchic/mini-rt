#include "ft_minirt.h"
#include "libft.h"

static int	parse_bonus_plane(char **tokens, t_scene *sc)
{
	int		status;
	t_obj	*object;

	status = parse_plane(tokens, sc);
	if (status)
	{
		object = sc->objs;
		while (object && object->next)
			object = object->next;
		if (object && object->type == OBJ_PLANE)
			((t_plane *)object->ptr)->material.checker = 1;
	}
	return (status);
}

int	dispatch(char **tokens, t_scene *sc)
{
	if (ft_strcmp(tokens[0], "A") == 0)
		return (parse_ambient_light(tokens, sc));
	if (ft_strcmp(tokens[0], "C") == 0)
		return (parse_camera(tokens, sc));
	if (ft_strcmp(tokens[0], "L") == 0)
		return (parse_light(tokens, sc, 0));
	if (ft_strcmp(tokens[0], "sp") == 0)
		return (parse_sphere(tokens, sc));
	if (ft_strcmp(tokens[0], "pl") == 0)
		return (parse_plane(tokens, sc));
	if (ft_strcmp(tokens[0], "cy") == 0)
		return (parse_cylinder(tokens, sc));
	if (ft_strcmp(tokens[0], "l") == 0)
		return (parse_light(tokens, sc, 1));
	if (ft_strcmp(tokens[0], "co") == 0)
		return (parse_cone_bonus(tokens, sc));
	if (ft_strcmp(tokens[0], "pl#") == 0)
		return (parse_bonus_plane(tokens, sc));
	return (0);
}

int	parse_file_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		status;
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i] || line[i] == '#')
		return (1);
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
		return (free_split(tokens), 1);
	status = dispatch(tokens, scene);
	free_split(tokens);
	return (status);
}
