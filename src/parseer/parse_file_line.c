#include "ft_minirt.h"
#include "libft.h"

static int	parse_bonus_plane(char **tok, t_scene *sc)
{
	int		ok;
	t_obj	*o;

	ok = parse_plane(tok, sc);
	if (ok)
	{
		o = sc->objs;
		while (o && o->next)
			o = o->next;
		if (o && o->type == OBJ_PLANE)
			((t_plane *)o->ptr)->material.checker = 1;
	}
	return (ok);
}

int	dispatch(char **tok, t_scene *sc)
{
	if (ft_strcmp(tok[0], "A") == 0)
		return (parse_ambient(tok, sc));
	if (ft_strcmp(tok[0], "C") == 0)
		return (parse_camera(tok, sc));
	if (ft_strcmp(tok[0], "L") == 0)
		return (parse_light(tok, sc, 0));
	if (ft_strcmp(tok[0], "sp") == 0)
		return (parse_sphere(tok, sc));
	if (ft_strcmp(tok[0], "pl") == 0)
		return (parse_plane(tok, sc));
	if (ft_strcmp(tok[0], "cy") == 0)
		return (parse_cylinder(tok, sc));
	if (ft_strcmp(tok[0], "l") == 0)
		return (parse_light(tok, sc, 1));
	if (ft_strcmp(tok[0], "co") == 0)
		return (parse_cone_bonus(tok, sc));
	if (ft_strcmp(tok[0], "pl#") == 0)
		return (parse_bonus_plane(tok, sc));
	return (0);
}

int	parse_file_line(char *line, t_scene *sc)
{
	char	**tokens;
	int		ok;
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!line[i] || line[i] == '#')
		return (1);
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
		return (free_split(tokens), 1);
	ok = dispatch(tokens, sc);
	free_split(tokens);
	return (ok);
}
