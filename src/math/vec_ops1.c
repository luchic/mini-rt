/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_ops1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 14:02:10 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 14:02:11 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

inline t_vec3	vdivv(t_vec3 a, float k)
{
	return (vec3(a.x / k, a.y / k, a.z / k));
}

inline double	dot_product(t_vec3 origin, t_vec3 direction)
{
	return (origin.x * direction.x + origin.y * direction.y + origin.z
		* direction.z);
}

inline t_vec3	vcross_product(t_vec3 a, t_vec3 b)
{
	return (vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y
			* b.x));
}
