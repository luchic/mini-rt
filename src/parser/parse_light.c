#include "ft_minirt.h"

static void	set_rgb(t_rgb *color, float value)
{
	color->red = value;
	color->green = value;
	color->blue = value;
}

static int	set_light(t_scene *scene, t_light *light, int bonus_multi)
{
	t_light	*it;

	if (!scene->lights)
		scene->lights = light;
	else
	{
		it = scene->lights;
		while (it->next)
			it = it->next;
		it->next = light;
	}
	if (!bonus_multi)
	{
		if (scene->has_l)
			return (0);
		scene->has_l = 1;
	}
	return (1);
}

int	parse_light(char **tokens, t_scene *scene, int bonus_multi)
{
	t_vec3	pos;
	float	brightness;
	t_rgb	color;
	t_light	*light;

	if (!tokens[1] || !tokens[2])
		return (0);
	if (!parse_v3(tokens[1], &pos))
		return (0);
	if (!parse_float(tokens[2], &brightness, 0.0f, 1.0f))
		return (0);
	if (tokens[3])
	{
		if (!parse_color(tokens[3], &color))
			return (0);
	}
	else
		set_rgb(&color, 1.0f);
	light = (t_light *)emalloc(sizeof(t_light));
	light->pos = pos;
	light->br = brightness;
	light->color = color;
	light->next = NULL;
	return (set_light(scene, light, bonus_multi));
}
