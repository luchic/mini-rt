#include "ft_minirt.h"

#ifdef BONUS

static int	parse_cone_metric(t_cone *co, char **tok)
{
	float	ang;
	float	height;

	if (!parse_float(tok[3], &ang, 0.1f, 89.9f))
		return (0);
	if (!parse_float(tok[4], &height, 0.0f, 1e6))
		return (0);
	co->ang = ang * PI_F / 180.0f;
	co->h = height;
	return (1);
}

int	parse_cone_bonus(char **tok, t_scene *sc)
{
	t_cone	*co;
	t_rgb	c;
	t_vec3	cent;
	t_vec3	axis;

	if (!tok[1] || !tok[2] || !tok[3] || !tok[4] || !tok[5] || tok[6])
		return (0);
	co = (t_cone *)emalloc(sizeof(t_cone));
	if (!parse_v3(tok[1], &cent))
		return (ft_free(co), 0);
	if (!parse_norm_v3(tok[2], &axis))
		return (ft_free(co), 0);
	if (!parse_cone_metric(co, tok))
		return (ft_free(co), 0);
	if (!parse_color(tok[5], &c))
		return (ft_free(co), 0);
	co->c = cent;
	co->a = axis;
	co->m.color = c;
	co->m.checker = 0;
	co->m.specular = 0.25f;
	co->m.sp_exp = 48;
	co->m.bump = 0;
	scene_add_obj(sc, new_obj(OBJ_CONE, co));
	return (1);
}
#else

int	parse_cone_bonus(char **tok, t_scene *sc)
{
	(void)tok;
	(void)sc;
	return (0);
}
#endif