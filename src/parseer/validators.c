#include "ft_minirt.h"

int	parse_float(const char *s, float *out, float minv, float maxv)
{
	int		ok;
	float	v;

	ok = 0;
	v = ft_atof_with_checker(s, &ok);
	if (!ok)
		return (0);
	if (v < minv || v > maxv)
		return (0);
	*out = v;
	return (1);
}

void	scene_add_obj(t_scene *sc, t_obj *node)
{
	t_obj	*it;

	if (!sc->objs)
	{
		sc->objs = node;
		return ;
	}
	it = sc->objs;
	while (it->next)
		it = it->next;
	it->next = node;
}
