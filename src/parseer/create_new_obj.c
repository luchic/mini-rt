#include "ft_minirt.h"

t_obj	*new_obj(int type, void *ptr)
{
	t_obj	*n;

	n = (t_obj *)emalloc(sizeof(t_obj));
	n->type = (t_objtype)type;
	n->ptr = ptr;
	n->next = NULL;
	return (n);
}
