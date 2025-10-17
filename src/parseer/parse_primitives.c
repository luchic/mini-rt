#include "ft_minirt.h"

int	parse_ambient(char **tok, t_scene *sc)
{
	float	ratio;
	t_rgb	c;

	if (sc->has_a)
		return (0);
	if (!tok[1] || !tok[2] || tok[3])
		return (0);
	if (!parse_float(tok[1], &ratio, 0.0f, 1.0f))
		return (0);
	if (!parse_color(tok[2], &c))
		return (0);
	sc->amb = ratio;
	sc->amb_color = c;
	sc->has_a = 1;
	return (1);
}

int	parse_camera(char **tok, t_scene *sc)
{
	float	fov;
	t_vec3	pos;
	t_vec3	direction;

	if (sc->has_c)
		return (0);
	if (!tok[1] || !tok[2] || !tok[3] || tok[4])
		return (0);
	if (!parse_v3(tok[1], &pos))
		return (0);
	if (!parse_norm_v3(tok[2], &direction))
		return (0);
	if (!parse_float(tok[3], &fov, 0.0f, 180.0f))
		return (0);
	sc->camera.pos = pos;
	sc->camera.direction = direction;
	sc->camera.fov_deg = fov;
	sc->has_c = 1;
	return (1);
}
