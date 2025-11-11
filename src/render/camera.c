/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:37:00 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/27 13:58:42 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static t_vec3	choose_up(t_vec3 direction)
{
	t_vec3	up;

	up = vec3(0, 1, 0);
	if (fabsf(direction.y) > 0.99f)
		up = vec3(0, 0, 1);
	return (up);
}

void	camera_build(t_camera *camera)
{
	t_vec3	up;

	up = choose_up(camera->direction);
	camera->right = vnorm(vcross_product(camera->direction, up));
	camera->up = vnorm(vcross_product(camera->right, camera->direction));
}
