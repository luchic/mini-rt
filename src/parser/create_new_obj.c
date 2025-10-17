#include "ft_minirt.h"

t_obj	*new_obj(int type, void *ptr)
{
	t_obj	*object;

	object = (t_obj *)emalloc(sizeof(t_obj));
	object->type = (t_objtype)type;
	object->ptr = ptr;
	object->next = NULL;
	return (object);
}
