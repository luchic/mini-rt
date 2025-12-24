/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 14:02:26 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 14:02:27 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_vec3	vec3_project_on_axis(t_vec3 v, t_vec3 axis)
{
	return (vmul(axis, dot_product(v, axis)));
}

t_vec3	vec3_reject_from_axis(t_vec3 v, t_vec3 axis)
{
	return (vsub(v, vec3_project_on_axis(v, axis)));
}
