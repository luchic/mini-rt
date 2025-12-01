
#include "ft_minirt.h"
#include <string.h>



int	main(int argc, char **argv)
{
	t_app app;

	if (argc != 2)
		ft_exit("Usage: ./miniRT <scene.rt>", 1);
	init_app(&app, argv[1]);
	water_init(&app);
	render(&app);

	setup_hooks(&app);
	mlx_loop(app.mlx);
	image_destroy(&app);
	if (app.mlx)
		mlx_terminate(app.mlx);
	return (0);
}
