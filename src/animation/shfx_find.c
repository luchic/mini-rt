/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shfx_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:44:45 by yyudi             #+#    #+#             */
/*   Updated: 2025/12/24 12:44:46 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
