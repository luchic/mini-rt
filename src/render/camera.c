/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:37:00 by yyudi             #+#    #+#             */
/*   Updated: 2025/10/17 16:11:48 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static t_vec3	choose_up(t_vec3 direction)
{
	t_vec3	up;

	up = v3(0, 1, 0);
	if (fabsf(dir.y) > 0.99f)
		up = v3(0, 0, 1);
	return (up);
}

void	camera_build(t_camera *camera)
{
	t_vec3	up;

	up = choose_up(camera->direction);
	camera->right = vnorm(vcross(camera->direction, up));
	camera->up = vnorm(vcross(camera->right, camera->direction));
}
