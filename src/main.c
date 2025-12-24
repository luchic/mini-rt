/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 14:02:07 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 14:02:08 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"
#include <string.h>

int	main(int argc, char **argv)
{
	t_app	app;

	ft_bzero(&app, sizeof(t_app));
	if (argc != 2)
		ft_exit("Usage: ./miniRT <scene.rt>", 1);
	init_app(&app, argv[1]);
	set_render_context(&app);
	render(&app);
	setup_hooks(&app);
	mlx_loop(app.mlx);
	image_destroy(&app);
	if (app.mlx)
		mlx_terminate(app.mlx);
	ft_clean();
	return (0);
}
