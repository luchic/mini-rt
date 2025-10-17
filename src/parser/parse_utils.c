#include "ft_minirt.h"

int	parse_float(const char *str, float *out, float minv, float maxv)
{
	int		ok;
	float	v;

	ok = 0;
	v = ft_atof_with_checker(str, &ok);
	if (!ok)
		return (0);
	if (v < minv || v > maxv)
		return (0);
	*out = v;
	return (1);
}

void	scene_add_obj(t_scene *scene, t_obj *node)
{
	t_obj	*it;

	if (!scene->objs)
	{
		scene->objs = node;
		return ;
	}
	it = scene->objs;
	while (it->next)
		it = it->next;
	it->next = node;
}
