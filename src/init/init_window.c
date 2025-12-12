#include "ft_minirt.h"

static void	image_create(t_app *app, int width, int height)
{
	app->img.img = mlx_new_image(app->mlx, width, height);
	if (!app->img.img)
	{
		mlx_terminate(app->mlx);
		ft_exit("mlx_new_image failed", 1);
	}
	app->img.width = width;
	app->img.height = height;
	if (mlx_image_to_window(app->mlx, app->img.img, 0, 0) < 0)
	{
		mlx_delete_image(app->mlx, app->img.img);
		mlx_terminate(app->mlx);
		ft_exit("mlx_image_to_window failed", 1);
	}
}

static void	init_window(t_app *app)
{
	app->width = WIN_W;
	app->height = WIN_H;
	app->mlx = mlx_init(app->width, app->height, "miniRT", false);
	if (!app->mlx)
		ft_exit("mlx_init failed", 1);
	image_create(app, app->width, app->height);
}

void	init_app(t_app *app, const char *scene)
{
	if (!has_rt_extension(scene))
		ft_exit("Usage: ./miniRT <scene.rt>", 1);
	ft_bzero(app, sizeof(t_app));
	if (!parse_file(scene, &app->scene))
		ft_exit("parse failed", 1);
	camera_build(&app->scene.camera);
	init_camera_animation(app);
	rng_seed(app, 2463534242u);
	app->lamp_enabled = 0;
	init_window(app);
}
