#include "ft_minirt.h"

t_obj	*find_first(t_scene *sc, t_objtype type)
{
	t_obj	*o;

	if (!sc)
		return (NULL);
	o = sc->objs;
	while (o)
	{
		if (o->type == type)
			return (o);
		o = o->next;
	}
	return (NULL);
}

t_plane	*find_ground(t_scene *sc)
{
	t_obj	*o;

	o = find_first(sc, OBJ_PLANE);
	if (o)
		return ((t_plane *)o->ptr);
	return (NULL);
}
