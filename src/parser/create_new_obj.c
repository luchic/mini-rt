/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:05:55 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 13:05:56 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
