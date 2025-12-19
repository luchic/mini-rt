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

static int	parse_light_color(char *token, t_rgb *color)
{
	if (token)
	{
		if (!parse_color(token, color))
			return (0);
	}
	else
		set_rgb(color, 1.0f);
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
	if (!parse_light_color(tokens[3], &color))
		return (0);
	light = (t_light *)emalloc(sizeof(t_light));
	light->type = LIGHT_POINT;
	light->pos = pos;
	light->dir = vec3(0.0f, -1.0f, 0.0f);
	light->br = brightness;
	light->color = color;
	light->cutoff_cos = -1.0f;
	light->next = NULL;
	return (set_light(scene, light, bonus_multi));
}
