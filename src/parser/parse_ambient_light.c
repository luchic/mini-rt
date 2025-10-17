#include "ft_minirt.h"

int	parse_ambient_light(char **tokens, t_scene *scene)
{
	float	ratio;
	t_rgb	color;

	if (scene->has_a)
		return (0);
	if (!tokens[1] || !tokens[2] || tokens[3])
		return (0);
	if (!parse_float(tokens[1], &ratio, 0.0f, 1.0f))
		return (0);
	if (!parse_color(tokens[2], &color))
		return (0);
	scene->amb = ratio;
	scene->amb_color = color;
	scene->has_a = 1;
	return (1);
}