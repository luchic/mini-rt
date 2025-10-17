#include "ft_minirt.h"

static void	set_rgb(t_rgb *color, float value)
{
	color->red = value;
	color->green = value;
	color->blue = value;
}

static int	set_light(t_scene *sc, t_light *light, int bonus_multi)
{
	t_light	*it;

	if (!sc->lights)
		sc->lights = light;
	else
	{
		it = sc->lights;
		while (it->next)
			it = it->next;
		it->next = light;
	}
	if (!bonus_multi)
	{
		if (sc->has_l)
			return (0);
		sc->has_l = 1;
	}
	return (1);
}

int	parse_light(char **tok, t_scene *sc, int bonus_multi)
{
	t_vec3	pos;
	float	br;
	t_rgb	c;
	t_light	*light;

	if (!tok[1] || !tok[2])
		return (0);
	if (!parse_v3(tok[1], &pos))
		return (0);
	if (!parse_float(tok[2], &br, 0.0f, 1.0f))
		return (0);
	if (tok[3])
	{
		if (!parse_color(tok[3], &c))
			return (0);
	}
	else
		set_rgb(&c, 1.0f);
	light = (t_light *)emalloc(sizeof(t_light));
	light->pos = pos;
	light->br = br;
	light->color = c;
	light->next = NULL;
	return (set_light(sc, light, bonus_multi));
}
